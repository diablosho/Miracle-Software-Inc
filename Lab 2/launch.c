#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define	CHILD	0
#define	INIT	0
#define	PARENT	1
#define	ERROR	2

typedef	struct COMMAND_ARGUMENTS
{
	int		argc;
	char	*argv;
	char	**envp;
} structArgs;

void PrintChildReturnValueOnStderr(int childPID)
{
	fprintf(stderr, "Child PID Return Value:\t%i\n", childPID);
}

structArgs ConstructChildExecARGS(structArgs originalArgs)
{
	char* newARGV		=	(char*)malloc(sizeof(char)	*	(originalArgs.argc - 1));
	int newArgc = 1;
		
	for (newArgc = 1; newArgc < originalArgs.argc; newArgc++)
		newARGV[newArgc] = originalArgs.argv[newArgc + 1];
		
	structArgs newArgs = { newArgc, newARGV, originalArgs.envp };
	
	return newArgs;
}

void ExecuteProcess(structArgs newProcessArgs)
{
	//	execve(const char* path, const char* args[], const char* envp[]);
	//	execvp(const char* file, const char* args[]);
	execvp(newProcessArgs.argv[1], newProcessArgs.argv);
}

int main(int argc, char *argv, char** envp)
{
	structArgs args = { argc, argv, envp };
	int	typeOfProcess = PARENT;
	int	childReturnValue = INIT;
	int childPID = fork();

	if (childPID > 0)		typeOfProcess = PARENT;
	else if (childPID == 0)	typeOfProcess = CHILD;
	else if (childPID < 0)	typeOfProcess = ERROR;

	switch (typeOfProcess)
	{
		case PARENT:
		{
			printf("Child PID:\t\t%i\n", childPID);
			wait(&childReturnValue);
			printf("Child Return Value:\t%i\n", childReturnValue);
			break;
		}
		case CHILD:
		{
			if (args.argc >= 2)	ExecuteProcess(ConstructChildExecARGS(args));
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
