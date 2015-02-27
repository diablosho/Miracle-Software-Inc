#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#define NOARGS -1
#define SUCCESS 0