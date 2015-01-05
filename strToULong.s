/*
 * Filename: strToULong.s
 * Author: Gurkirat Singh
 * Description: Given a base and a string, convert that string to an unsigned
 *		long int. Bases can be decimal, octal, hexadecimal, etc. If
 *		errno is not 0, then return the converted string to int value.
 *		If endptr is not 0, then that means there is an error.
 */

PTRSIZ = 4		!The size of the pointer
endptrOffset = 4	!the offset of the end pointer

 	.global strToULong	!declare global variable so we can use it
				!from other files
	.section ".text"	!Text segment begins here

/*
 * Function name: strToULong()
 * Function prototype: unsigned long strToULong(const char* str,const int base)
 * Description: Converts the input parameter to unsigned long
 * Paramters:
 *	arg1: const char* str -- string that needs to be converted to unsigned
 *		long
 *	arg2: const int base -- base that the str should be converted long into
 * Side Effects: The string might not be a valid input
 * Error Conditions: String is not an integer; unsuccessful convert
 * Return Value: returns the unsigned long of the input string
 * 
 * Register Used:
 *	%i0 - arg 1 -- string that needs to be converted to unsigned long
 *	%i1 - arg 2 -- base that long int should be in
 *	
 *	%g0 -- just for comparison with 0
 *	%l2 -- value for errno
 *	%l3 -- value of ptrError
 *	%l4 -- value for end pointer
 *	%l1 -- char value of end pointer
 */

 strToULong:
 	save	%sp, -(92 + PTRSIZ) & -8, %sp	!Save caller's window
						!Take account of the pointer
						!size
	
	set	errno, %l2			!set a reg for errno 
	st	%g0, [%l2]			!reset errno to 0
	
	mov	%i0, %o0			!string that needs conversion
	sub	%fp, endptrOffset, %l4		!-4 to move %fp by 4 bytes

	mov	%l4, %o1			!store end pointer value
	mov	%i1, %o2			!store base in local reg

	call	strtoul				!convert string to unsigned
	nop					!long int
	
	ld	[%l2], %l0			!errno might have changed

	cmp	%g0, %l0
	bne	errno_nonzero			!errno is not zero
	nop

	ld	[%l4], %l1
	ldub	[%l1], %l1			!get the char that end ptr
						!is pointing at
	cmp	%g0, %l1			!if endptr is not zero,there
	bne	endptr_NOK			!is an error
	nop

	mov	%o0, %i0			!return unsigned long back
	ba	returnValue
	nop

errno_nonzero:
	mov	%g0, %i0			!Return 0 when errno is nonzero
	ba	returnValue
	nop

endptr_NOK:
	set	ptrError, %l3			!set errno to ptrError
	ld	[%l3], %l3
	st	%l3, [%l2]

	ba	errno_nonzero			!return 0
	nop

returnValue:
	ret					!Return from subroutine
	restore					!Restore call'ers window
