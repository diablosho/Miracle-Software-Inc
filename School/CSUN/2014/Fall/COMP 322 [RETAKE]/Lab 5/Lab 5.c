#include "Lab 5.h"

int main(int argc, char* argv[], char** envp[])
{
	int argVCounter = 1;

	if (argc == 1)
		return NOARGS;
	for (argVCounter = 1; argVCounter < argc; argVCounter++)
		Output(strtoul(argv[argVCounter], NULL, 10), ((strtoul(argv[argVCounter], NULL, 10) & rangePageIndices) >> 12), (strtoul(argv[argVCounter], NULL, 10) & rangePageOffsets));
	return SUCCESS;
}