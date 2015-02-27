; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 04, Part 1		(Part 1.asm)
;
; This program 

INCLUDE Irvine32.inc

.data
num1	SBYTE 32
num2	SWORD 32
num3	SDWORD 32
num4	DWORD 01234ABCDh
num5	SBYTE -1
num6	BYTE 255
num7	LABEL BYTE
nums1	WORD 0ABCDh, 01234h, 02468h, 01359h

.code
Part_1 PROC
	;mov al, num1
	;call dumpregs
	;mov ax, num2
	;call dumpregs
	;mov eax, num3
	;call dumpregs
	;mov eax, num4
	;call dumpregs
	;mov al, num1 
	;call dumpregs
	;movzx eax, num1
	;call dumpregs
	;mov al, num5
	;call dumpregs
	;movsx eax, num5
	;call dumpregs
	
	;mov eax, 0
	;mov al, num1
	;call dumpregs
	;xchg al, ah
	;call dumpregs

	;mov ax, nums1
	;call dumpregs
	;mov ax, nums1 + 2
	;call dumpregs

	;unsigned carry (addition)
	;mov al, num6
	;call dumpregs
	;add al, 5
	;call dumpregs
	;sub al, 5
	;call dumpregs

	; signed sign and overflow
	;mov al, num1
	;sub al, 33
	;call dumpregs
	;overflow
	;mov al, num1
	;add al, +127
	;call dumpregs

	;underflow
	;mov al, num1
	;sub al, 160
	;call dumpregs

	;OFFSET
	;mov esi, OFFSET num1
	;call dumpregs
	;mov esi, OFFSET num3
	;call dumpregs

	;PTR
	;mov al, BYTE PTR num4
	;call dumpregs

	;TYPE
	;mov al, TYPE num4
	;call dumpregs

	;LENGTHOF
	;mov al, LENGTHOF nums1
	;call dumpregs

	;SIZEOF
	;mov al, SIZEOF nums1
	;call dumpregs

	;LABEL
	;mov al, num7
	;call dumpregs 

	;mov eax, 1
	;call writeint
	;call crlf
	
exit
Part_1 ENDP
END Part_1