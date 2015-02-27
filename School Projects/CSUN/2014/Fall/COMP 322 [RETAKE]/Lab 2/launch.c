#include "ProcessFunctions.h"

int ProcessChild(int argc, char* argv[], int typeOfProcess, int childPID)
{
	char** newARGV	=	CreateNewARGV(argc, argv);
	execv(newARGV[0], newARGV);
	return SUCCESS;
}

int ProcessParent(int argc, char* argv[], int typeOfProcess, int childPID)
{
	int childExitValue = SUCCESS;
	fprintf(stderr, "%s:  $$ = %i\n", argv[1], childPID);
	waitpid(childPID, &childExitValue, NULL);
	fprintf(stderr, "%s:  $? = %i\n", argv[1], childExitValue);
	return childExitValue;
}

int main(int argc, char *argv[])
{
	int childPID = fork();
	int typeOfProcess = GetProcessType(childPID);
	switch (typeOfProcess)
	{
		case CHILD:
		{
			ProcessChild(argc, argv, CHILD, childPID);
			break;
		}
		case PARENT:
		{
			ProcessParent(argc, argv, PARENT, childPID);
			break;
		}
		case ERROR:
		{
			printf("FORKING ERROR\n");
			return ERROR;
		}
	}

	return SUCCESS;
}