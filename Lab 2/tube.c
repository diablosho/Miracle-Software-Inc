#include "BriansHeaderFile.h"

static int pipes;



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