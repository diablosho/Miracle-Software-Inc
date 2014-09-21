#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BRIAN_H_INCLUDED
#define BRIAN_H_INCLUDED

//	Functions between here...
#define	CHILD				0
#define	INIT				0
#define	INITIAL_CHILDREN	0
#define	SUCCESS				0
#define	PARENT				1
#define	FORKING_ERROR		2

int		childExitValue		=	INIT,
		childPID			=	PARENT,
		retval				=	SUCCESS,
		childRetVal			=	INIT,
		typeOfProcess		=	PARENT;
		childProcessCounter =	INITIAL_CHILDREN;

int		ForkMe()
{
	childPID = fork();
	typeOfProcess = GetProcessType(childPID);
	return SUCCESS;
}
int		GetProcessType(int childPID)
{
	if (childPID > 0)		return PARENT;
	else if (childPID == 0)	return CHILD;
	else if (childPID < 0)	return FORKING_ERROR;
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
