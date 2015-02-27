; NAME:			Brian Jones
; ASSIGNMENT:	Chapter 06, Exercise 10		(main.asm)
; DATE:			2012-04-25
;
; This program will calculate all the Fibonacci numbers (sequentially) until the Carry flag is set.
; It does this by Initializing the values of n, n-1, and n-2 to 2, 1, and 0 (respectively).  Then, for
; each iteration of the loop, (n-1) and (n-2) will be summed together, and checked for a set Carry-Flag.
; If no CF is set, then (n-2) and (n-1) are shifted, making (n-2) = (n-1), and (n-1) = sum.  Finally, the
; loop will then be iterated again, thus continuing the cycle until the CF becomes set, telling us we have
; found the maximum number of Fibonacci numbers, in sequence, that can be made within our date-size (DWORD).

INCLUDE Irvine32.inc					; Included for DumpRegs and exit macro

.data
n			DWORD	2
nMinusOne	DWORD	1
nMinusTwo	DWORD	0

.code									; code segment begins
main PROC								; begin main procedure
	mov eax, 0							; mov 0 into EAX
	call WriteDec						; print First Number (0)
	call CrLf							; Move cursor to next line
	
	mov eax, 1							; mov 1 into EAX
	call WriteDec						; print Second Number (1)
	call CrLf							; Advance Cursor to next line

;----------------------------------------------------------------------------------------
;					Start the function, and check the CF status							|
;----------------------------------------------------------------------------------------

nextIteration:
	mov eax, nMinusTwo					; mov (n-2) into eax
	add eax, nMinusOne					; add [eax, or (n-1)], and (n-2), and store in eax
	jc carryFlagSet						; if CF set, jump to carryFlagSet
	
	call WriteDec						; output sum to the screen
	call CrLf							; Move cursor to the next line

	push nMinusOne						; push (n-1) onto the stack to...
	pop nMinusTwo						; ...make the new (n-2) equal (n-1)
	push eax							; push eax (sum) onto the stack to...
	pop nMinusOne						; ...make the new (n-1) equal the sum
	inc n								; increment the value of n and...
	jmp nextIteration					; ...jump to the next loop iteration

carryFlagSet:
	exit								; macro to halt program execution
	main ENDP							; end of "main" procedure
END main								; EOF/startup procedure marker