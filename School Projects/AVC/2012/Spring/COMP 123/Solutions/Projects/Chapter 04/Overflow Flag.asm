; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 04, Part 1, Exercise 3		(Overflow Flag.asm)
;
; This program 

INCLUDE Irvine32.inc		; Included for DumpRegs call and exit macro

.data
NUM1	SBYTE	 7Fh		; 01111111
NUM2	SBYTE	 01h		; 00000001

.code						; Code segment begins
Overflow_Flag_main PROC		; Start main procedure
	
	mov ah, NUM1			; AH = 01111111
	add	ah, NUM2			; AH = 01111111 + 00000001 = 010000000 (9 bits)
	call DumpRegs			; Output Register Contents to Screen

exit						; Halt program execution
Overflow_Flag_main ENDP		; End of main procedure
END Overflow_Flag_main		; EOF