;	NAME:		BRIAN JONES
;	DATE:		05/02/2012
;	PROJECT:	CHAPTER 7, ASSIGNMENT 7
;	COURSE:		CIS-123 (INTRO TO ASSEMBLY LANGUAGE)
;	
;	This program will prompt the user for a number.  It will then determine if that number is a prime number
;	or not (and also if it is -1 to terminate the program).  It does this by looping through every number
;	between 1 and the number, dividing the number by the current loop-index.  If the remainder of that
;	operation is 0, then we know that the number is not prime, since it is evenly divisible by 3 numbers.
;	If the remainder is NOT 0, then we know that the number IS prime, since it is only divisible by itself
;	and 1.  The program then displays whether the number is prime or not, and then starts over again.
;	It will repeat this process until -1 is entered, which is the sentinel value for program termination.

TITLE MASM PrimeNumbers						(main.asm)

INCLUDE Irvine32.inc

.data
promptForNumber BYTE	"Enter a number (greater than 1) to check if it is prime or not (-1 to exit):  ", 0
isPrimeMsg		BYTE	"...IS PRIME", 0
isNotPrimeMsg	BYTE	"...NOT PRIME", 0

.code
main PROC
	Prompt:	
		mov EDX, OFFSET promptForNumber
		call WriteString					; Output message prompt for number
		call ReadInt						; Input a number from the user
		cmp EAX, -1							; Check if number is sentinel value
		je finished							; If it's sentinel value, terminate program
		cmp EAX, 1							; compare the number to 1, and...
		jle Prompt							; ...if <= it is invalid, so start over.
		call isPrime						; We have valid input, now let's check if Prime
		jmp Prompt							; Start again
	finished:
		exit								; We're done!!!
main ENDP

isPrime	PROC
	mov ECX, EAX							; mov user input into ECX as divisor-counter
	sub ECX, 1								; subtract 1 from ECX
	StillNotSure:
		cmp ECX, 1							; compare divisor with 1, and...
		je NumIsPrime						; ...if =, the loop ran all-the-way, so is prime
		push eax							; save dividend
		cdq									; sign-extend eax
		div ecx								; Divide user-input by divisor-counter
		pop eax								; Restore numerator (user-input) for future operations
		cmp edx, 0							; Compare remainder with 0, and...
		je NumIsNotPrime					; ...if equal, we know we don't have a prime number
		loop StillNotSure					; Decrement divisor-counter and check again
	NumIsPrime:
		mov EDX, OFFSET isPrimeMsg			; Prepare the "IS PRIME" message for output
		call WriteString					; Output the "IS PRIME" message
		call CrLf							; Move to the next line
		jmp TerminateProcedure				; Terminate the Procedure
	NumIsNotPrime:
		mov EDX, OFFSET isNotPrimeMsg		; Prepare the "IS NOT PRIME" message for output
		call WriteString					; Output the "IS NOT PRIME" message
		call CrLf							; Move to the next line
	TerminateProcedure:
		ret									; Finished with number, return to main program
isPrime	ENDP

END main