/*
 * Filename: toggle.s
 * Author: Gurkirat Singh
 * Description: This subroutine toggles the bit that isn't set in the original
 *		light bank array.
 */

FOUR = 4
	.global toggle		!declare global variable 

	.section ".text"	!text section starts here

/*
 * Function: toggle()
 * Function prototype: void toggle(unsigned int lightBank[], const unsigned
 *			int bank0, const unsigned int bank1);
 * Description: Toggles the lights according to the banks provided and if the
 *		lights are already on. Use xor operation to toggle bits.
 * Paramters:
 *		arg1 -- unsigned int lightBank[] -- array that contains two 
 *			ints of which we will toggle the bits
 *		arg2 -- const unsigned int bank0 -- bank 0 that we will use to
 *			compare the lightBank array with
 *		arg3 -- const unsigned int bank1 -- bank 1 that we will use to
 *			compare the lightBank array with
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * Registers Used:
 *	%l0 -- store the xor result of bank0 and first index in lightBank array
 *	%l1 -- store the xor result of bank1 and second index in Bank array
 */

toggle:
	save	%sp, -96, %sp		!save caller's window 

	ld	[%i0], %l0		!load first index of array
	ld	[%i0 + FOUR], %l1	!load second index of array

	xor	%l0, %i1, %l0		!toggle first index
	xor	%l1, %i2, %l1		!toggle second index

	st	%l0, [%i0];		!store result back in 1st index
	st	%l1, [%i0 + FOUR];	!store result bank in 2nd index

	ret				!return 
	restore
