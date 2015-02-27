; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 04, Part 1, Exercise 4		(Direct-Offset Addressing.asm)
; DATE:			2012-02-25
;
; This program will store 4 word values into two arrays (4 word values / 4 s-word values)
; Then, it will move each value of each array index into different registers, while
; Sign/Zero extending them to fit into larger registers.  It will also Output the contents
; of each register after the final value of each array is transferred to its' register.

INCLUDE Irvine32.inc						; Included for DumpRegs call, and exit macro

.data										; Data segment begins
Uarray WORD		1000h, 2000h, 3000h, 4000h	; [0]=1000h, [1]=2000h, [2]=3000h, [3]=4000h
Sarray SWORD	-1, -2, -3, -4				; [0]=  -1h, [1]=  -2h, [2]=  -3h, [3]=  -4h

.code										; Code segment begins
Direct_Offset_Addressing_main PROC			; Main procedure
	
	movzx EAX, [Uarray]						; Zero-Extend move Uarray[0] into EAX
	movzx EBX, [Uarray+2]					; Zero-Extend move Uarray[1] into EBX
	movzx ECX, [Uarray+4]					; Zero-Extend move Uarray[2] into ECX
	movzx EDX, [Uarray+6]					; Zero-Extend move Uarray[3] into EDX
	call DumpRegs								; Output registers to Screen
	movsx EAX, [Sarray]						; Sign-Extend move Sarray[0] into EAX
	movsx EBX, [Sarray+2]					; Sign-Extend move Sarray[1] into EBX
	movsx ECX, [Sarray+4]					; Sign-Extend move Sarray[2] into ECX
	movsx EDX, [Sarray+6]					; Sign-Extend move Sarray[3] into EDX
	call DumpRegs								; Output registers to Screen

exit										; halt program execution
Direct_Offset_Addressing_main ENDP			; End of main procedure
END Direct_Offset_Addressing_main			; EOF