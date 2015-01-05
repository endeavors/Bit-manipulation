/*
 * Filename: printChar.s
 * Author: Gurkirat Singh
 * Description: SPARC assembly routine that prints out the character argument
 *		to stdout.
 */

 	.global printChar	!Declares the variable so we can access it
				!outside this file
	
	.section ".data"	!The data segment begins here
fmt:				!Formatted string used for printf()
	.asciz "%c"		

	.section ".text"	!The text segment begins here

/*
 * Function name: printChar()
 * Function prototype: void printChar( char ch);
 * Description: Prints the passed in argument through printf()
 * Parameters:
 * 	arg 1: char ch -- the character that is going to be printed
 * 
 * Side Effects: Outputs a single characters that is the argument
 * Error Conditions: None
 * Return Value: None
 *
 * Register Used: 
 *	%i0 - arg 1 -- the characters that is the argument of this function
 *	
 *	%o0 - param 1 to printf() -- format string
 *	%o1 - param 2 to printf() -- copy of arg 1 being passed in
 */

 printChar:
 	save	%sp, -96, %sp	!Save caller's window

	set	fmt, %o0	!Format string
	mov	%i0, %o1	!Copy the paramter to output register
	call	printf		!Printf call
	nop			!Delay slot

	ret			!Return from subroutine
	restore			!Restore caller's window
