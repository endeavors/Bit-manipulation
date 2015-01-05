/*
 * Filename: displayLights.s
 * Author: Gurkirat Singh
 * Description: Cycles through an array of size 2 and prints '*' if light is on
 *		or '-' if it is off using printChar. A new line character is 
 *		printed before this subroutine ends. This program uses bit mask
 *		of 1 and shifts left logical to extract each bit after it is 
 *		"and-ed" using the bitwise & operator.
 */

BITMASK = 0x80000000		!bitmask of 1 to get most significant bit		
ASTERISK = '*'			!light is on
HYPHEN = '-'			!light is off
NEWLINE = '\n'
SPACE = ' '
FOUR = 4
INTEGER_BIT = 32		!counter to keep track when to switch to next
				!index

 	.global displayLights	!Declare global variable so we can call it from
				!another file
	
	.section ".text"	!The text segment begins here

/*
 * Function: displayLights()
 * Function prototype: void displayLights(const unsigned int lightBank[]);
 * Description: Displays the light banks by printing them using '*' to show
 *		that the light is on and '-' to indicate if the light is off
 * Paramters: 
 *	arg1: const unsigned int lightBank[] -- light bank that we need to 
 *		display
 * Side Effects: Masking bit while keeping track of counter
 * Error Conditions: None 
 * Return Value: None
 * Registers Used:
 *	%i0 - arg 1 -- int array that contains 2 indexes
 *	%l0 -- counter that tracks when to switch to next index of array
 *	%l1 -- original int that stays unchanged throughout program
 *	%l2 -- value of bitmask is stored here
 *	%l3 -- shifted left logical value (int)
 *	%l4 -- result (int) after bitmasking
 *	%l5 -- flag set to switch to second index
 */

displayLights:
 	
	save	%sp, -96, %sp		!Save caller's window

	clr	%l2			!clear local registers so we have their
	clr	%l0			!intial value set to 0. 
	clr	%l1
	clr	%l5

	set	BITMASK, %l2		!store bitmask hex inside local reg

	ld	[%i0], %l1		!load first index to local register
	mov	%l1, %l3		!make copy of local register that has
					!the value of first index of array

LoopOver:
	and	%l3,%l2 , %l4		!Bitmask first index with bitwise &
					!operator to extract MSB
	cmp	%l4, %l2		!compare if result is equal to value
	be	One			!of bitmask, if it is, then print
	nop				!'*'

	mov	HYPHEN, %o0		!Turn light off, print '-'
	call	printChar
	nop

PartOfLoop:
	inc	%l0			!increment counter to see when to
					!switch to next index
	cmp	%l0, INTEGER_BIT	!if counter is still in bank 1,
	bl	CheckSpace		!then keeping looping to bitmask
	nop
	
	cmp	%l5, %g0		!check if flag to go to 2nd index set?
	be	SecondIndex		!switch to 2nd index
	nop

	ba	Return			!Done with both 1st and 2nd index
	nop

SecondIndex:

	mov	1, %l5			!Set flag to track that it's currently
	clr	%l0			!on second index
	ld	[%i0 + FOUR], %l1	!load second index from array
	mov	%l1, %l3		!make copy of second index

	mov	SPACE, %o0		!add space character before starting
	call	printChar		!2nd index
	nop

	ba	LoopOver		!go through the same loop extract bits
	nop				!individually

CheckSpace:
	mov     %l0, %o0		!check if 4 bits have been printed
 	mov     FOUR, %o1		!if they have, then print space before
  	call    .rem			!printing next bit
	nop

	cmp     %o0, %g0		!print space after 4 bits
        be      Space
        nop

ShiftLeft:
	sll	%l3, 1, %l3		!shift left logical by 1 bit, then
	ba	LoopOver		!continue looping to & for bitmask
	nop

Space:
	mov	SPACE, %o0		!print space character between bits
	call	printChar
	nop

	ba	ShiftLeft		!keep shifting int to the left
	nop
One:
	mov	ASTERISK, %o0		!Turn light on by printing
	call	printChar		!'*' by using printChar
	nop
	
	ba	PartOfLoop
	nop

Return:
	mov	NEWLINE, %o0		!print newline after we are done with
	call	printChar		!printing light on/off
	nop

	ret				!Return from subroutine
	restore				!Restore caller's window
