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

void	GetPipeHandle(int pipes[], int typeOfCommunication)
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
char**	ParseCommands()
{
	return NULL;
}
void	SendCommands(char** commands)
{

}
char*	GetCommand()
{
	return NULL;
}
void	RunCommand(char* command)	//	First Child does first command, second child does second command...
{
	//execve()
}
//	...and here!!!
#endif