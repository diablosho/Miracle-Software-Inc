; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 05, Exercise 06		(main.asm)
; DATE:			2012-02-25
;
; This program will generate 20 strings with 10 random Capitalized Characters, and then
; output them to the screen

INCLUDE Irvine32.inc						; Included for DumpRegs and exit macro

.data
RandomString	BYTE	"----------", 0dh, 0ah, 0
RandChar		BYTE	?

.code										; code segment begins
main PROC									; begin main procedure
	mov ecx, 20d							; mov 20d into main string counter
	call Randomize							; initialize Random-Seed Value

	NextString:
		call RandomizeString				; Generate Random String
		loop NextString						; Repeat while main string counter > 0
	
	exit									; macro to halt program execution
	main ENDP								; end of "main" procedure

;----------------------------------------------------------------------------------------
RandomizeString PROC	USES ECX
;	
;	Create the String of 10 Capitalized Characters and Outputs them to the Screen
;	
;	Registers:	EAX = Range of Characters for Randomization
;	41h to 5Bh = 'A' to 'Z'
;
;----------------------------------------------------------------------------------------

	mov ecx, 10d							; move 10d into character-counter
NextChar:
	mov eax, 25d							; move 25d into EAX, to set the range of possible characters
	call RandomRange						; Generate a random integer
	add eax, 41h							; add 41h ('A') to EAX, converting the random # into a character
	push eax								; push character onto the stack for later retrieval
	loop NextChar							; repeat while character-counter > 0
	
	mov ecx, 10d							; 10 characters in the RandomString
FillString:
	pop eax									; Retrieve the last letter from the stack
	mov BYTE PTR [RandomString+ecx-1], al	; move the last letter into the String
	loop FillString							; repeat while character-index > 0
	
	mov edx, OFFSET RandomString			; mov the Memory Address of RandomString into EDX
	call WriteString						; Output the contents of RandomString to the Screen
	ret										; return to main procedure (line 21)
RandomizeString ENDP						; end of RandomizeString Procedure

END main		; EOF/startup procedure marker