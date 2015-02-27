; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 03, Exercise 1		(Exercise 1.asm)
;
; This program subtracts three 16-bit integers from each other, 
;	dumping register outputs after each operation.

INCLUDE Irvine32.inc				; Included for DumpRegs and exit macro

.data
NUM1	WORD	5555h		; Initialize WORD-SIZE NUM1 with 5555h
NUM2	WORD	3333h		; Initialize WORD-SIZE NUM2 with 3333h
NUM3	WORD	1111h		; Initialize WORD-SIZE NUM3 with 1111h

.code						; code segment begins
Exercise1_main PROC			; begin "Exericse1_main" procedure
	
	mov	ax, NUM1			; move NUM1 (5555h) into AX
	sub ax, NUM2			; subtract NUM2 (3333h) from AX, giving 2222h
	call DumpRegs			; call DumpRegs to output registers to screen
	sub ax, NUM3			; subtract NUM3 (1111h) from AX, giving 1111h
	call DumpRegs			; call DumpRegs to output registers to screen

	exit					; macro to halt program execution
Exercise1_main ENDP			; end of "Exercise2_main" procedure
END Exercise1_main			; EOF/startup procedure marker