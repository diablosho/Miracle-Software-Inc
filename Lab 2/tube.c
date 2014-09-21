#include "ProcessFunctions.h"
#define FIRST_FORK	0
#define	SECOND_FORK	1

static int pipes;

void ProcessParent(int* childPID, structArgs cmdArgs)
{
	fprintf("Child1 PID:\t%i\n", childPID[FIRST_FORK]);
	fprintf("Child2 PID:\t%i\n", childPID[SECOND_FORK]);

	structArgs* listCommands	=	CreateCommandList(cmdArgs.argc, cmdArgs.argv);
	SendCommands(cmdArgs);
}

void ProcessChild(int childNum)
{
	switch (childNum)
	{
	case FIRST_FORK:	GetPipeHandle(pipes, READ_PIPE); break;
	case SECOND_FORK:	GetPipeHandle(pipes, WRITE_PIPE); break;
	}
	
	RunCommand(command);
}

int main(int argc, char* argv[])
{
	int typeProcess[2] = { PARENT, PARENT };
	int pipes[2];	//	READ = 0, WRITE = 1
	int childPID[2]	= { PARENT, PARENT };
		
	int retvalPipe = pipe(pipes);
	childPID[FIRST_FORK] = fork();
	typeProcess[FIRST_FORK] = GetTypeProcess(childPID[FIRST_FORK]);

	switch (typeProcess[FIRST_FORK])
	{
		case CHILD:	//	Child 1 reads from stdin and executes the program
		{
			ProcessChild(FIRST_FORK);
			
			break;
		}
		case PARENT:
		{
			childPID[SECOND_FORK] = fork();
			if (childPID[SECOND_FORK] == CHILD)	//	Child 2 reads from stdin and executes the program
			{
				GetPipeHandle(pipes, READ_PIPE);
				command = GetCommand();
				RunCommand(command);
				break;
			}

			while (!(childPID[FIRST_FORK] > 0 && childPID[SECOND_FORK] > 0));
			
			ProcessParent();

			break;
		}
		case ERROR:	{	break;	}
	}

	return 0;
}