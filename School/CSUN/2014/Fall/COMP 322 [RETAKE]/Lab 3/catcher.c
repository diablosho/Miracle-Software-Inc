#include "catcher.h"

void signalHandler(int numSignal)		//	Signal-Handler function
{
	signal(numSignal, signalHandler);	//	Unix automatically resets the signal-handler to it's default function, unless we re-assign the handler to our handler function
	int table_index = 0;

	if (numSignal != SIGTERM)	countSIGTERM = 0;
	else						countSIGTERM++;

	for (table_index = 0; table_index <= LAST_SIGNAL && tableSignals[table_index].signalInt != numSignal; table_index++);

	fprintf(stdout, "SIG%s caught at %i\n", tableSignals[table_index].signalName, time(NULL));		//	Print signal caught
	fflush(stdout);						//	Flush stdout to clear the buffer
	countSignals++;
}

int main(int argc, char* argv[])
{
	countSIGTERM = 0;
	countSignals = 0;

	fprintf(stderr, "%s:  $$ = %i\n", argv[0], getpid());
	//	ASSIGN HANDLERS TO EACH SIGNAL DESIGNATED IN THE COMMAND-LINE ARGUMENTS
	int argCounter = 1;
	for (argCounter = 1; argCounter < argc; argCounter++)
	{
		int signal_index = 0;
		for (signal_index = 0; signal_index <= LAST_SIGNAL; signal_index++)
			if (strcmp(tableSignals[signal_index].signalName, argv[argCounter]) == 0)
				signal(tableSignals[signal_index].signalInt, signalHandler);
	}
	
	for (;;)
	{
		pause();
		if (countSIGTERM >= 3)
		{
			fprintf(stderr, "%s:  Total signals count = %i\n", argv[0], countSignals);
			return 0;
		}
	}

	return 0;
}