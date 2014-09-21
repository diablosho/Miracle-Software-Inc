#include "Lab2.h"

int ProcessChild(int argc, char* argv[], int typeOfProcess, int childPID)
{
	char** newARGV	=	CreateNewARGV(argc, argv);
	execv(newARGV[0], newARGV);
	return childExitValue;
}

int ProcessParent(int argc, char* argv[], int typeOfProcess, int childPID)
{
	fprintf(stderr, "%s:  $$ = %i\n", argv[1], childPID);
	waitpid(childPID, &childExitValue, NULL);
	fprintf(stderr, "%s:  $? = %i\n", argv[1], childExitValue);
}

int main(int argc, char *argv[])
{
	ForkMe();

	switch (typeOfProcess)
	{
		case CHILD:
		{
			ProcessChild(argc, argv, typeOfProcess, childPID);
			break;
		}
		case PARENT:
		{
			ProcessParent(argc, argv, typeOfProcess, childPID);
			break;
		}
		case FORKING_ERROR:
		{
			printf("FORKING ERROR\n");
			return FORKING_ERROR;
		}
	}

	return SUCCESS;
}