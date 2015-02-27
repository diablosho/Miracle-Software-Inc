; NAME:			Brian Jones
; ASSIGNMENT:	Extra Credit 01		(Extra Credit 1.asm)
; DATE:			2012-02-25
;
; This program will input an integer target-sum from the user, 
; and then determine every combination of sequential integers that
; add up to the user-supplied target-sum integer

INCLUDE Irvine32.inc						; Included for DumpRegs and exit macro

.data
Output_String_1	BYTE	"Enter a target sum to process:  ", 0
Output_String_2	BYTE	"The first and last numbers in every series of positive, "
				BYTE	"consecutive integers", 0dh, 0ah
				BYTE	"whose sum is 30 are:  ", 0dh, 0ah, 0
Output_String_3 BYTE	" ... ", 0

InputSum			DWORD	1				; Variable for User-Input
RunningTotal		DWORD	1				; Variable for Current Sum
FirstNumber			DWORD	1				; Variable for First Number
LastNumber			DWORD	1				; Variable for Last Number

.code										; code segment begins
main PROC									; begin main procedure
	call IntroFormat						; Basic formatting and data input
	call ProcessNumbers						; Process First and Last Numbers
		
	exit									; macro to halt program execution
	main ENDP								; end of "main" procedure

;----------------------------------------------------------------------------------------
IntroFormat	PROC
;
;	Prompts the user for Input, and stores that input into InputSum variable
; 
;	Registers:	EDX = Data Buffer for WriteString
;				EAX = Data Buffer for Input Target-Sum
;----------------------------------------------------------------------------------------
	mov edx, OFFSET Output_String_1			; move "prompt 1" into edx
	call WriteString						; prompt the user to input an integer
	call ReadInt							; read an integer from the user
	mov InputSum, eax						; move target-sum into the InputSum variable
	mov edx, OFFSET Output_String_2			; move main message into EDX for WriteString
	call WriteString						; Output main message
	ret
IntroFormat ENDP

;----------------------------------------------------------------------------------------
ProcessNumbers PROC
;
;	Processes every combination of sequential integers whose sums equal InputSum
; 
;	Registers:	ECX = Reverse-Counter for First-Number Incrementing Loop
;				EAX = First Number
;----------------------------------------------------------------------------------------
	mov ecx, InputSum
StartAgain:
	mov eax, FirstNumber					; move FirstNumber into EAX
	mov LastNumber, eax						; move FirstNumber into LastNumber
	call FindLastNumber						; Find final number in sequence (if any)
	inc FirstNumber							; Increment FirstNumber
	loop StartAgain							; while FirstNumber < InputSum, start again
	ret
ProcessNumbers ENDP

;----------------------------------------------------------------------------------------
FindLastNumber PROC USES ECX
;
;	Sequentially adds every number after the first number together until either:
;		1:	The Running-Total is EQUAL to the InputSum
;		2:  The Running-Total is GREATER-THAN the InputSum
;
;	Registers:	ECX = Reverse-Counter for Last-Number Incrementing Loop
;				EAX = Running-Total Counter
;----------------------------------------------------------------------------------------
	mov ecx, InputSum				; Set ECX to InputSum, for last-number counter
KeepGoing:
	inc LastNumber					; increment final number in sequence to test
	add eax, LastNumber				; add LastNumber to EAX
	mov RunningTotal, eax			; store EAX as RunningTotal
	cmp eax, InputSum				; compare EAX (RunningTotal) and InputSum
	je OutputNumbers				; if RunningTotal = InputSum, go to OutputNumbers;
	jl KeepGoing					; if RunningTotal < InputSum, go back to Start again
	ret								; return to ProcessNumbers Procedure (Line 46)
;----------------------------------------------------------------------------------------
OutputNumbers:	
;
;	Code block dedicated to displaying calculated integers
;
;	Registers:	EAX = Holds data for use with WriteDec function
;				EDX = Data Buffer for WriteString
;----------------------------------------------------------------------------------------
	mov eax, FirstNumber					; move FirstNumber into EAX
	call WriteDec							; Output FirstNumber to the Screen
	mov edx, OFFSET Output_String_3			; move the address of Output_String_3 to EDX
	call WriteString						; Output Output_String_3 to the Screen
	mov eax, LastNumber						; move LastNumber into EAX
	call WriteDec							; Output LastNumber to the Screen
	call Crlf								; Move to the beginning of the next line
	ret										; return to ProcessNumbers Procedure (Line 46)
FindLastNumber ENDP

END main		; EOF/startup procedure marker