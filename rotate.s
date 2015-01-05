
/*
 * Filename: rotate.s
 * Author: Gurkirat Singh
 * Description: This subroutine shifts the bits right or left according to the
 *		sign bit; it takes into account the last 6 bits of the count
 *		integer.
 */ 

MSB_MASK = 0x80000000		!most significant bit
LSB_MASK = 0x00000001		!least significant bit
SIXBIT_MASK = 0x0000003F 	!mask for last 6 bits
FOUR = 4			!int byte offset
LASTBIT = 31			
	.global rotate
	
	.section ".text"
			 
/*
 * Function: rotate()
 * Function prototype:void rotate(unsigned int lightBank[],const int rotateCnt)
 * Description: This function rotates the current light patterns by the rotate
 *		count. If rotate count is positive, rotate left and if negative
 *		then rotate right. Bits are not lost in this process.
 * Parameters:
 *	arg1 -- unsigned int lightBank[] -- array of 2 ints that are our lights
 *	arg2 -- const int rotateCnt -- number of times we need to rotate bits
 * Side Effects: None
 * Error Conditions: check if rotate count is 0; if it is, return immediately
 * Return Value:None
 * Registers Used:
 *      %l0 -- value of first index of lightBank
 *      %l1 -- value of second index of lightBank
 *      %l2 -- value of sign bit of shift count
 *      %l3 -- value of lower six bits of shift count
 *	%l4 -- stores the ANDed result of 2 values
 *	%l5 -- counter to keep track of shiftCount
 *	%l6 -- sets flag to 1 if ripple count is negative
 *	%l7 -- gets the most significant bit of ripple count
 */

rotate:
	save    %sp, -96, %sp		!save caller's window

	cmp     %g0, %i1		!check if ripple count is 0
	be      return			!return if ripple count is 0
	nop

	ld      [%i0], %l0		!load 1st index from array
	ld      [%i0 + FOUR], %l1		!load 2nd index
		
	clr     %l5			!clear local registers to be
	clr     %l6			!used later in the file
	clr     %l4
		
	set     MSB_MASK, %l2           !get the sign of the most significant
	and     %l2, %i1, %l7           !bit
	
	cmp     %g0, %l7                !postive: shift left
					!negative: shift right
	be      setFlag			!sign bit was set (was positive)
	nop

convertToPos:
	sub     %g0, %i1, %i1		!subtract from 0 to get positive
	ba      getSixBits		!value of ripple count
	nop

setFlag:
	mov     1, %l6			!set flag that ripple count was 
					!negative

getSixBits:
	set     SIXBIT_MASK, %l3	!mask the ripple count to get the last
	and     %l3, %i1, %l3		!6 bits of it

	cmp	%g0, %l3		!if mask produces 0, then return
	be	done			!immediately
	nop

	cmp     %g0, %l6		!shift accordingly to the sign bit
	bne     shift_left		!of ripple count
	nop

shift_right:
	and     %l0, LSB_MASK, %l4	!get the least significant bit
	and	%l1, LSB_MASK, %l7	!of both indexes in array

	sll     %l4, LASTBIT, %l4	!shift left to move the bits as 
	sll	%l7, LASTBIT, %l7		!most significant bits

	srl     %l0, 1, %l0		!shift the original int by 1 to right
	srl     %l1, 1, %l1

	or      %l4, %l1, %l1		!officialy set the stored bits to the
	or	%l7, %l0, %l0		!original integers

	inc     %l5 			!increment counter
	cmp     %l5, %l3		!check if another loop is possible
	bl      shift_right
	nop
	
	ba      done			!we are done, exit
	nop

shift_left:
	and     %l1, %l2, %l4		!get most significant bit of both
	and	%l0, %l2, %l7		!indexes
	
	srl     %l4, LASTBIT, %l4	!move stored bits to lowest significant
	srl	%l7, LASTBIT, %l7	!bit position

	sll     %l1, 1, %l1		!shift the original integers left by 1
	sll     %l0, 1, %l0
	
	or      %l4, %l0, %l0		!combine the stored bits with the 
	or	%l7, %l1, %l1		!original integers
	
	inc     %l5			!increment counter
	cmp     %l5, %l3		!check if rotate count value has been
	bl      shift_left		!reached for another loop
	nop

done:
	st      %l0, [%i0]		!store 1st index back in array
	st      %l1, [%i0 + FOUR]	!store 2nd index back in array

return:
	ret				!Return from subroutine
	restore				!Restore caller's window
