#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PROCESS_FUNCTIONS_H_INCLUDED
#define PROCESS_FUNCTIONS_H_INCLUDED

#define CHILD		0
#define INIT		0
#define SUCCESS		0
#define	READ_PIPE	0
#define PARENT		1
#define	WRITE_PIPE	1
#define ERROR		2

typedef struct ARGUMENTS
{
	int		argc;
	char**	argv;
	char*	command;
} structArgs;

int		GetPipeHandle(int pipes[], int typeOfCommunication)
{
	switch (typeOfCommunication)
	{
		case READ_PIPE:
		{
			dup2(stdin, pipes[READ_PIPE]);	//	So we can read from parent with stdin
			close(pipes[WRITE_PIPE]);
			break;
		}
		case WRITE_PIPE:
		{
			dup2(stdout, pipes[WRITE_PIPE]);	//	So we can read from parent with stdin
			close(pipes[READ_PIPE]);
			break;
		}
	}
}
int		GetProcessType(int childPID)
{
	if (childPID > 0)		return PARENT;
	else if (childPID == 0)	return CHILD;
	else if (childPID < 0)	return ERROR;
}
char**	CreateNewARGV(int argc, char* argv[])	//	Malloc the memory space for newARGV, so that it can take argv's values without memory faults
{
	int		newARGC = 0;
	char**	newARGV = (char**)malloc(sizeof(char*)*(argc - 1));

	for (newARGC = 0; newARGC < argc; newARGC++)
	{
		newARGV[newARGC] = (char*)malloc(sizeof(argv[newARGC + 1]));
		newARGV[newARGC] = argv[newARGC + 1];
	}
	return newARGV;
}
structArgs*	CreateCommandList(int argc, char* argv[])
{
	structArgs*	cmdArgs;
	char**		newArgv;
	char*		command;
	int			commandNumber = 0;
	int			startingPosition	=	0;
	int			lastPosition = 0;
	int			newArgc = 0;
		
	do
	{
		startingPosition = lastPosition;
		for (newArgc = 0; lastPosition < argc; lastPosition++, newArgc++)
		{
			if (argv[lastPosition] == ",")
			{
				lastPosition++;
				break;
			}
		}

		cmdArgs[commandNumber].argc = newArgc;
		int i = 0;
		for (i = 0; i < newArgc; i++)
		{
			newArgv[i] = (char*)malloc(sizeof(argv[startingPosition + i]));
			newArgv[i] = argv[startingPosition + i];
			sprintf(command, newArgv[i]);
			sprintf(command, " ");
		}
		structArgs newCmd = { newArgc, newArgv, command };
		cmdArgs[commandNumber] = newCmd;
		commandNumber++;
	} while (lastPosition < argc);
	return cmdArgs;
}

char**	ParseCommand(structArgs cmdArgs)
{
	
	return NULL;
}
void	SendCommand(structArgs cmdArgs)	//	Used to send a complete command to a child process
{
	
}
char*	GetCommand(structArgs cmdArgs)	//	Used by child process to grab a full set of argv[], argc, etc.
{
	return NULL;
}
void	RunCommand(structArgs cmdArgs)	//	Used by child process to run command retrieved by GetCommand()
{
	//execve()
}
//	...and here!!!
#endif