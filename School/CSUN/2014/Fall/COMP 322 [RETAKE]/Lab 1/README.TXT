Name:		Brian Jones
Class:		Comp 322
Assignment:	time-4-baby-and-me (Lab 1)
Date:		9/12/2014

Original (9/12/2014 @ 23:15):
-This program *was* working properly, but at the moment I am getting a Memory Fault when running the program.
-Once I switched my implementations of the System/User-times, I began to hard-fault immediately upon execution.
-I am still working on this bug (I just ran out of time before the deadline), which most likely relates to the 
	memory-mapped structure array pInfo or struct tms.

Implemented:
-getpid()
-getppid()
-Output to Screen

Still to be implemented:
-GetSysUserTimes() (to retrieve the system and user times for the parent and child);