; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 04, Part 1, Exercise 2		(Zero and Sign Flags.asm)
;
; This program 

INCLUDE Irvine32.inc

.data
NUM1 BYTE  00000001b
NUM2 BYTE  00000001b
NUM3 BYTE -00000001b

.code
Zero_and_Sign_Flags_main PROC
	
	mov ah, NUM3
	add ah, NUM1
	call DumpRegs
	sub ah, NUM2
	call DumpRegs

exit
Zero_and_Sign_Flags_main ENDP
END Zero_and_Sign_Flags_main