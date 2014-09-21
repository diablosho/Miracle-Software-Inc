#include "ProcessFunctions.h"
#define FIRST_FORK	0
#define	SECOND_FORK	1

static int pipes;

int main(int argc, char* argv[])
{
	int typeProcess[2] = { PARENT, PARENT };
	int pipes[2];	//	READ = 0, WRITE = 1
	int childPID[2]	= { PARENT, PARENT };
	char** command;
	
	int retvalPipe = pipe(pipes);
	childPID[FIRST_FORK] = fork();
	typeProcess[FIRST_FORK] = GetTypeProcess(childPID[FIRST_FORK]);

	switch (typeProcess[FIRST_FORK])
	{
		case CHILD:	//	Process first command
		{
			ProcessChild(FIRST_FORK);
			GetPipeHandle(pipes, READ_PIPE);
			command = GetCommand();
			RunCommand(command);
			break;
		}
		case PARENT:
		{
			childPID[SECOND_FORK] = fork();
			if (childPID[SECOND_FORK] == CHILD)
			{
				GetPipeHandle(pipes, WRITE_PIPE);
				command = GetCommand();
				RunCommand(command);
				break;
			}

			while (!(childPID[FIRST_FORK] > 0 && childPID[SECOND_FORK] > 0));
			
			fprintf("Child1 PID:\t%i\n", childPID[FIRST_FORK]);
			fprintf("Child2 PID:\t%i\n", childPID[SECOND_FORK]);
						
			command = ParseCommands();
			SendCommands(command);
			
			break;
		}
		case ERROR:	{	break;	}
	}

	return 0;
}