/*
 * Filename: ripple.s
 * Author: Gurkirat Singh
 * Description: Rotates the current light patterns and then displays the lights
 */

FOUR = 4	/* int byte offset */
NEGONE = -1	/* ripple by -1 */
POSONE = 1	/* ripple by 1 */

	.global ripple

	.section ".text"

/*
 * Function: ripple()
 * Function prototype:void ripple(unsigned int lightBank[],cont int rippleCnt);
 * Description: This program calls rotate to rotate one bit at a time and then
 *		displays the lights after each rotate to cause a ripple.
 * Parameters:
 *	arg1 -- int lightBank[] -- int array that holds two light banks; these
 *				are just two different integers
 *	arg2 -- int rippleCnt	-- how many times it must cause a ripple
 * Side Effects:Can display ripple twice depending on where displayLights is
 *		called in main.c and also, ripple count cannot be 0. 
 * Error Conditions: Returns immediately if ripple count is 0
 * Return value: None
 * Registers used:
 *	%l0 -- holds the first index of lightbank array
 *	%l1 -- holds the second index of lightbank array
 *	%l2 -- counter how many times ripple needs to loop
 *	%l3 -- flag which sets to 1 when negative ripple is inputted.
 */

ripple:
	save	%sp, -96, %sp		!save caller's window
	
	cmp	%g0, %i1		!check if ripple count is 0
	be	done			!if it is, return immediately
	nop

	clr	%l0			!0 index
	clr	%l1			!1st index
	clr	%l2			!counter
	clr	%l3			!flag

	ld	[%i0], %l0		!load first index from array
	ld	[%i0 + FOUR], %l1	!load second index from array

	
	cmp	%i1, %g0		!check if ripple count is negative
	bl	convertToPos		!or positive. Convert to positive if
	nop				!negative

	ba	Loop			!if ripple count is positive, begin
	nop				!the loop 

convertToPos:
	sub	%g0, %i1, %i1		!make int positive
	mov	POSONE, %l3		!set Flag-was negative before

Loop:
	mov	%i0, %o0		!set first argument of rotate
BeginLoop:
	
	mov	%o0, %o0
	cmp	%g0, %l3		!rippleCnt is positive
	bne	getNegativeCount	!flag was set, so pass -1 as the input
	nop

	mov	POSONE, %o1		!no flag was set, pass 1 as input

continueLoop:
	call	rotate			!call rotate 1 bit at a time
	nop

	call	displayLights		!display lights right now rotating
	nop				!1 bit each time

	inc	%l2			!increment counter to know how many
					!time to ripple

	cmp	%l2, %i1		!check if we have reached the count
	bl	BeginLoop		!of ripple count; if not, then loop
	nop				!again

	ba	done			!we are done, exit
	nop

getNegativeCount:
	mov	NEGONE, %o1		!pass in -1 at the input to rotate
	ba	continueLoop		!and then go back where we left off
	nop

done:
	ret				!Return from subroutine
	restore				!Restore caller's window



