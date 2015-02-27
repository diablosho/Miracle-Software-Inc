; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 04, Part 1, Exercise 1		(Carry Flag.asm)
;
; This program 

INCLUDE Irvine32.inc

.data
NUM1 BYTE 00000000b
NUM2 BYTE 00000001b

.code
Carry_Flag_main PROC

	mov ah, NUM1
	sub ah, NUM2
	call DumpRegs
	add ah, NUM2
	call DumpRegs

exit
Carry_Flag_main ENDP
END Carry_Flag_main