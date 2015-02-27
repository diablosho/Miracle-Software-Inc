; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 03, Exercise 2		(Exercise 2.asm)
;
; This program will define variables for the following data types:
;		BYTE, SBYTE, WORD, SWORD, DWORD, SDWORD
; It will then move each variable into the proper registers,
;		and then dump the Registers to the screen (one at a time).

INCLUDE Irvine32.inc				; Included for DumpRegs and exit macro

.data
byteVar		BYTE	       001h		; byteVar	=	 01d
sbyteVar	SBYTE	      -002h		; sbyteBar	=	-02d
wordVar		WORD	     00003h		; wordVar	=	 03d
swordVar	SWORD	    -00004h		; swordVar	=	-04d
dwordVar	DWORD	 000000005h		; dwordVar	=	 05d
sdwordVar	SDWORD	-000000006h		; sdwordVar	=	-06d

.code								; code segment begins
Exercise2_main PROC					; begin "Exericse2_main" procedure
	
	mov	ah, byteVar					; move 01d into ah
	call DumpRegs					; dump the registers
	mov al, sbyteVar				; move -02d into al
	call DumpRegs					; dump the registers
	mov ax, wordVar					; move 03d into ax			
	call DumpRegs					; dump the registers
	mov ax, swordVar				; move -04d into ax
	call DumpRegs					; dump the registers
	mov eax, dwordVar				; move 05d into eax
	call DumpRegs					; dump the registers
	mov eax, sdwordVar				; move -06d into eax
	call DumpRegs					; dump the registers

	exit							; macro to halt program execution
Exercise2_main ENDP					; end of "Exercise2_main" procedure
END Exercise2_main					; EOF/startup procedure marker