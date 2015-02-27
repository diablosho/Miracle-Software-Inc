#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#define	ERROR		-1
#define LAST_SIGNAL	28

typedef struct
{
	char* signalName;
	int signalInt;
} SIGNAL;

static SIGNAL tableSignals[] =
{
	{ "HUP", SIGHUP },
	{ "INT", SIGINT },
	{ "QUIT", SIGQUIT },
	{ "ILL", SIGILL },
	{ "TRAP", SIGTRAP },
	{ "ABRT", SIGABRT },
	{ "IOT", SIGIOT },
	{ "BUS", SIGBUS },
	{ "FPE", SIGFPE },
	{ "KILL", SIGKILL },
	{ "USR1", SIGUSR1 },
	{ "SEGV", SIGSEGV },
	{ "USR2", SIGUSR2 },
	{ "PIPE", SIGPIPE },
	{ "ALRM", SIGALRM },
	{ "TERM", SIGTERM },
	{ "STKFLT", SIGSTKFLT },
	{ "CHLD", SIGCHLD },
	{ "CONT", SIGCONT },
	{ "STOP", SIGSTOP },
	{ "TSTP", SIGTSTP },
	{ "TTIN", SIGTTIN },
	{ "TTOU", SIGTTOU },
	{ "URG", SIGURG },
	{ "XCPU", SIGXCPU },
	{ "XFSZ", SIGXFSZ },
	{ "VTALRM", SIGVTALRM },
	{ "PROF", SIGPROF },
	{ "WINCH", SIGWINCH }
};

static int countSIGTERM;
static int countSignals;