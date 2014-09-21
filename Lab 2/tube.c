#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CHILD	0
#define PARENT	1
#define ERROR	2

static int pipes;

char** CreateNewARGV(int argc, char* argv[])	//	Malloc the memory space for newARGV, so that it can take argv's values without memory faults
{
	int newARGC = 0;
	char** newARGV = (char**)malloc(sizeof(char*)*(argc - 1));	//	Initialize enough memory for [argc-1] strings (A.K.A. char*);  char** = char[]* = char[][]

	for (newARGC = 0; newARGC < argc; newARGC++)
	{
		newARGV[newARGC] = (char*)malloc(sizeof(argv[newARGC + 1]));
		newARGV[newARGC] = argv[newARGC + 1];
	}
	
	return newARGV;	//	Return pointer to a char**
}

char** ParseCommands()
{
	return NULL;
}

void SendCommands(char** commands)
{

}

char* GetCommand()
{
	return NULL;
}

void RunCommand(char* command)	//	First Child does first command, second child does second command...
{
	//execve()
}

int GetTypeProcess(int pid)
{
	int typeProcess = PARENT;
	if (pid < 0)		typeProcess = ERROR;
	else if (pid == 0)	typeProcess = CHILD;
	else if (pid > 0)	typeProcess = PARENT;
	return typeProcess;
}

int main(int argc, char* argv[])
{
	int typeProcess1	=	PARENT,
		typeProcess2	=	PARENT;
	int pipes[2],	//	READ = 0, WRITE = 1
		pid1 = PARENT,
		pid2 = PARENT;
	char** command;
	
	int retvalPipe = pipe(pipes);
	
	dup2(stdout, pipes[1]);	//	So we can write to children with stdout
	close(pipes[0]);

	pid1 = fork();

	switch (typeProcess1 = GetTypeProcess(pid1))
	{
		case CHILD:	//	Process first command
		{
			dup2(stdin, pipes[0]);	//	So we can read from parent with stdin
			close(pipes[1]);
			command = GetCommand();
			RunCommand(command);
			break;
		}
		case PARENT:
		{
			pid2 = fork();
			if (pid2 == CHILD)
			{
				dup2(stdin, 0);
				close(pipes[1]);
				command = GetCommand();
				RunCommand(command);
				break;
			}

			while (!(pid1 > 0 && pid2 > 0));
			
			fprintf("Child1 PID:\t%i\n", pid1);
			fprintf("Child2 PID:\t%i\n", pid2);
						
			command = ParseCommands();
			SendCommands(command);
			
			break;
		}
		case ERROR:	{	break;	}
	}

	return 0;
}