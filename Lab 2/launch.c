#include <stdio.h>
#include <stdlib.h>

#define	CHILD	0
#define	INIT	0
#define	SUCCESS	0
#define	PARENT	1
#define	ERROR	2

int GetProcessType(int childPID)
{
	if (childPID > 0)		return PARENT;
	else if (childPID == 0)	return CHILD;
	else if (childPID < 0)	return ERROR;
}

char** CreateNewARGV(int argc, char* argv[])	//	Malloc the memory space for newARGV, so that it can take argv's values without memory faults
{
	int newARGC = 0;
	char** newARGV = (char**)malloc(sizeof(char*)*(argc-1));

	for (newARGC = 0; newARGC < argc; newARGC++)
	{
		newARGV[newARGC] = (char*)malloc(sizeof(argv[newARGC + 1]));
		newARGV[newARGC] = argv[newARGC + 1];
	}
	return newARGV;
}

int main(int argc, char *argv[])
{
	int	typeOfProcess = PARENT;
	int	childReturnValue = INIT;
	char** newARGV;
	int argIndex = 0;

	int childPID = fork();
	
	switch (GetProcessType(childPID))
	{
		case CHILD:
		{
			newARGV = CreateNewARGV(argc, argv);
			execv(newARGV[0], newARGV);
			exit(SUCCESS);
		}
		case PARENT:
		{
			fprintf(stderr, "%s:  $$ = %i\n", argv[1], childPID);
			waitpid(childPID, &childReturnValue, NULL);
			fprintf(stderr, "%s:  $? = %i\n", argv[1], childReturnValue);
			break;
		}
		case ERROR:
		{
			printf("ERROR\n");
			break;
		}
	}

	return 0;
}