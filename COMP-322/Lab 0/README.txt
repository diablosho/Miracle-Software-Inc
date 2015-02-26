Name:		Brian Jones
Class:		Comp 322
Assignment:	zero-one.c (Lab 1)
Date:		9/4/2014


UPDATE 3 (9/4/2014 @ 10:37):
-Everything is now running properly


UPDATE 2 (9/1/2014 @ 12:13):
-Very minor corrections are needed as of now

CHANGES:
-Fixed error in ASCII character conversion algorithm (from 8-bit ASCII to 7-bit ASCII)
-Fixed Parity calculation algorithm
-Bit-Padding has been implemented
-Whitespace-ignoring algorithm has been implemented
-Stdin has been implemented

STILL TO BE IMPLEMENTED/CORRECTED:
-For some reason, the T.Error string is being appended to the Original Input Buffer string
-Corrections to the Parity-Calculation algorithm (for T.Error detection)
-Stdout still needs to be implemented




UPDATE 1 (8/31/2014 @ 23:53):
-This program is now nearly complete.
-Needs some corrections to the Parity calculation algorithm (for Parity and T.Error detection)
-Needs implementation for bit-padding on inputted bytes (if the string was too short)




Original (8/28/2014 @ 18:00):
-Thus far, this program has been written to handle very limited test cases.
-There is an issue with combining strings at the moment (which is going to be solved shortly)
-Once a function has been implemented to painlessly construct file-path strings, progress will
	pick up dramatically.

Implemented:
-Command-Line argument parsing
-Special Ascii characters
-Conversion from 8-character string to byte, and further to ascii character
-Outputs ascii character to the screen

Still to be implemented:
-stdin
-Unix-specific syntax
-Parity checking
