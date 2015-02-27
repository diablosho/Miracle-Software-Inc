/*
Process:  Clone repository to Comp322 linux drive, then test make it to make sure it works
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>

#define FAIL		-1
#define CHILD		0
#define	FALSE		0
#define	PASS		0
#define PARENT		1
#define	TRUE		1
#define INIT		0	//	INIT was = 2
#define START_TIME	0
#define	PID_TIME	1
#define	PPID_TIME	2
#define	STOP_TIME	3
#define	WAIT_TIME	4

int	typeProcess;
typedef struct PROCESS_INFORMATION
{
	long int	tSTART,	tSTOP,	tUSER,	tSYS;
	int			PID,	PPID,	RETVAL;	
} structPInfo;

void GetSysUserTimes(structPInfo* pInfo)
{
	struct tms	tInfo;
	times(&tInfo);

	pInfo[CHILD].tUSER	=	tInfo.tms_cutime;
	pInfo[CHILD].tSYS	=	tInfo.tms_cstime;
	pInfo[PARENT].tUSER =	tInfo.tms_utime;
	pInfo[PARENT].tSYS	=	tInfo.tms_stime;
}

void printInformation(structPInfo* pInfo)
{
	/*
	REAL TIME:	Example:	1234 seconds;	Difference of stop time - start time
	USER TIME:	Example:	234 seconds;	Amount of time the process is in Running state (ie:  Not waiting)
	SYS TIME:	Example:	3 seconds;		Amount of time for System Calls to be processed
	*/

	if (pInfo[PARENT].tSTART < pInfo[CHILD].tSTART)	printf("START:       \t%d\n", pInfo[PARENT].tSTART);
	else											printf("START:       \t%d\n", pInfo[CHILD].tSTART);
	printf("CHILD PPID:   \t%5d,\t", pInfo[CHILD].PPID);
	printf("CHILD PID:    \t%5d\n", pInfo[CHILD].PID);
	printf("PARENT PPID:  \t%5d,\t", pInfo[PARENT].PPID);
	printf("PARENT PID:   \t%5d,\t", pInfo[PARENT].PID);
	printf("PARENT CPID:  \t%5d,\t", pInfo[CHILD].PID);
	printf("CHILD RETVAL: \t%5d\n", pInfo[CHILD].RETVAL);
	printf("PARENT tUSER: \t%5d,\t", pInfo[PARENT].tUSER);
	printf("PARENT tSYS:  \t%5d\n", pInfo[PARENT].tSYS);
	printf("CHILD tUSER:  \t%5d,\t", pInfo[CHILD].tUSER);
	printf("CHILD tSYS:   \t%5d\n", pInfo[CHILD].tSYS);
	printf("STOP:         \t%5d\n", pInfo[PARENT].tSTOP);
}

int main()
{
	structPInfo*	pInfo = mmap(NULL, sizeof(pInfo)*2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	int PorC;	

	for (PorC = 0; PorC <= 1; PorC++)
	{
		pInfo[PorC].PID			=	INIT;
		pInfo[PorC].PPID		=	INIT;
		pInfo[PorC].RETVAL		=	INIT;
		pInfo[PorC].tSTART		=	INIT;
		pInfo[PorC].tSTOP		=	INIT;
		pInfo[PorC].tSYS		=	INIT;
		pInfo[PorC].tUSER		=	INIT;
	}

	typeProcess = fork();
	if (typeProcess < 0)		return FAIL;
	else if (typeProcess == 0)	typeProcess = CHILD;
	else if (typeProcess > 0)	typeProcess = PARENT;
	
	pInfo[typeProcess].tSTART = time(NULL);

	switch (typeProcess)
	{
		case CHILD:
		{
			pInfo[typeProcess].PID		=	getpid();
			pInfo[typeProcess].PPID		=	getppid();
			pInfo[typeProcess].RETVAL	=	PASS;
			return pInfo[typeProcess].RETVAL;
		}
		case PARENT:
		{
			wait(&pInfo[CHILD].RETVAL);
			pInfo[typeProcess].PID		=	getpid();
			pInfo[typeProcess].PPID		=	getppid();
			pInfo[typeProcess].RETVAL	=	PASS;
			pInfo[typeProcess].tSTOP	=	time(NULL);
			
			printf("Getting System and User times\n");
			GetSysUserTimes(pInfo);
			printInformation(pInfo);

			return pInfo[typeProcess].RETVAL;
		}
		default:		printf("ERROR FORKING\n");	return FAIL;
	}
	
	return FAIL;
}
