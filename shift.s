/*
 * Filename: shift.s
 * Author: Gurkirat Singh
 * Description: This subroutine shifts the bits right or left according to the
 *		sign bit; it takes into account the last 6 bits of the count
 *		integer.
 */

MSB_MASK = 0x80000000		!most significant byte
LSB_MASK = 0x00000001		!least significant byte
SIXBIT_MASK = 0x0000003F	!last 6 bits of shift count mask
INT_OFFSET = 4			!int byte offset
LASTBIT = 31	
	.global shift

	.section ".text"

/*
 * Functiona: shift()
 * Function prototype: void shift(unsigned int lightBank[],const int shiftCnt);
 * Description: This function shifts the current light patterns by the shift 
 *		count and if the shift count is positive, it shifts to the left
 *		and if negative, it shifts to the right. Bits are lost in this
 *		process
 * Parameters:
 *	arg1 -- unsigned int lightBank[] -- array of 2 ints that are our lights
 *	arg2 -- const int shiftCnt -- number of time we need to shift our bits
 * Side Effects: None
 * Error Conditions: check if shift count is zero
 * Return Value: None
 * Registers Used:
 *	%l0 -- value of first index of lightBank
 *	%l1 -- value of second index of lightBank
 *	%l2 -- value of sign bit of shift count
 *	%l3 -- value of lower six bits of shift count
 *	%l4 -- stores the ANDed result of 2 values
 *	%l5 -- counter that check if another loop is possible
 *	%l6 -- sets flag to 1 if shift count is negative
 *	%l7 -- gets the most significant bit of shift count
 */

shift:
	save	%sp, -96, %sp		!save caller's window

	cmp	%g0, %i1		!check if shift count is 0
	be	return			!return if shift count is 0
	nop

	ld	[%i0], %l0		!load 1st index from array
	ld	[%i0 + INT_OFFSET], %l1 !load 2nd index from array

	clr 	%l5			!clear local registers 
	clr	%l6
	clr	%l4

	set	MSB_MASK, %l2		!get the sign of the most significant
	and	%l2, %i1, %l7		!bit

	cmp	%g0, %l7		!postive: shift left
					!negative: shift right
	be	setFlag			!sign bit was set (was positive)
	nop

convertToPos:
	sub	%g0, %i1, %i1		!subtract from 0 to get positive
	ba	getSixBits		!shift count
	nop				!get last 6 bits of shift count

setFlag:
	mov	1, %l6			!set flag since shift count was neg

getSixBits:
	set	SIXBIT_MASK, %l3	!get the last 6 bits of shift count
	and	%l3, %i1, %l3

	cmp	%g0, %l3		!check if returned result was 0,
	be	done			!if it was, then return immediately
	nop

	cmp	%g0, %l6		!begin shifting according to the 
	bne	shift_left		!sign bit of shift count
	nop

shift_right:
	and	%l0, LSB_MASK, %l4	!get the least significant bit of
	sll	%l4, LASTBIT, %l4	!1st index of array
	srl	%l0, 1, %l0		!shift original int by 1 bit to right
	srl	%l1, 1, %l1		
	or	%l4, %l1, %l1		!combine the stored bits with the
					!shifted bits of int from lightBank

	inc	%l5			!increment counter
	cmp	%l5, %l3		!check if counter is equal to shift
	bl	shift_right		!count
	nop

	ba	done			!we are done, exit
	nop

shift_left:
	and	%l1, %l2, %l4		!get least significant bit 
	srl	%l4, LASTBIT, %l4	!move stored bits to highest sig.
	sll	%l1, 1, %l1		!bit position
	sll	%l0, 1, %l0
	or	%l4, %l0, %l0		!combine stored bits with original
					!integers

	inc	%l5			!increment counter

	cmp	%l5, %l3		!check if we reached the value of
	bl	shift_left		!shift count
	nop
done: 
	st	%l0, [%i0]		!store 1st index back in array
	st	%l1, [%i0 + INT_OFFSET]	!store 2nd index back in array
return:
	ret				!Return from subroutine
	restore				!Restore caller's window
