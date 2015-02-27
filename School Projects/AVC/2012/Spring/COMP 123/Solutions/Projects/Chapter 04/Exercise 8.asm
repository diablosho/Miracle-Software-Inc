; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 04, Part 2, Exercise 8		(Exercise 8.asm)
; DATE:			2012-02-25
;
; This program will copy each character from a source string (minus the null-terminator)
; into a destination string in reverse.

INCLUDE Irvine32.inc								; Included for DumpRegs and exit macro

.data
source		BYTE	"This is the source string", 0	; source null-terminated string
destination	BYTE	SIZEOF source DUP('#')			; destination buffer

.code												; code segment begins
Exercise8_main PROC									; begin "Exericse8_main" procedure
	
	mov ecx, LENGTHOF source						; move "source" character count to ECX
	mov esi, (OFFSET source + LENGTHOF source) - 2	; move last address of "source" to ESI
	mov edi, OFFSET destination						; move destination buffer offset to EDI
L1:
		mov al, [esi]				; move data at memory address ESI into AL
		mov [edi], al				; move AL into memory address EDI
		dec esi						; decrement "source" index
		inc edi						; increment "destination" index
		loop L1						; repeat while "source" index > 0

	mov esi, OFFSET destination						; move destination OFFSET into ESI
	mov ebx, 1										; move character length into EBX
	mov ecx, LENGTHOF destination-1					; move character count to ECX
	call DumpMem									; Output contents of memory to Screen

	exit											; Macro to halt program execution
Exercise8_main ENDP									; End of "Exercise8_main" procedure
END Exercise8_main									; EOF/startup procedure marker