/*
 * Filename: set.s
 * Author: Gurkirat Singh
 * Description: This subroutine sets the bit that isn't set in the original
 *		light bank array.
 */

FOUR = 4
 	.global set

	.section ".text"

/*
 * Function: set()
 * Function prototype: void set(unsigned int lightBank[], const unsigned
 *			int bank0, const unsigned int bank1);
 * Description: Set the lights based on which bits are set and which are not.
 *		It turns on the light if we want to set it and we do this
 *		by ORing it by the inputted bank0 or bank1.
 * Parameters:
 *	arg1 -- unsigned int lightBank[] -- int array of size 2 that holds
 *			two indices that we want to set the lights of
 *	arg2 -- const unsigned int bank0 -- determine the bits we want to set
 *	arg3 -- const unsigned int bank1 -- determine bits we want to set for
 *			bank1
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * Registers used:
 *	%l0 -- stores the OR result of 1st index and bank0
 *	%l1 -- stores the result of 2nd index and bank1 after we OR it
 */ 

set:
 	save	%sp, -96, %sp		!save caller's window

	ld	[%i0], %l0		!load 1st index
	ld	[%i0 + FOUR], %l1	!load 2nd index

	or	%l0, %i1, %l0		!set bits for 1st int
	or	%l1, %i2, %l1		!set bits for 2nd int by ORing it
	
	st	%l0, [%i0];		!store result back
	st	%l1, [%i0 + FOUR]

	ret				!Return from subroutine
	restore				!Restore caller's window
