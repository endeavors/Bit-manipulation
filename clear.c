/*
 * Filename: clear.c
 * Author: Gurkirat Singh
 * Description: Clears the bits by anding them if the light is alrady on
 */

 #include "pa2.h"


/* function prototype private to this file */
static int clearBits(int num, int bank);

/*
 * Function name: clear()
 * Function prototype: void clear( unsigned int lightBank[], const unsigned
 *                      int bank0, const unsigned int bank1);
 * Description: This function clears the lights by anding them if the light is
 *              already on.
 * Parameters:
 *              arg1 -- int array that holds the two integers (light banks)
 *              arg2 -- int that bank0 needs to be set to
 *              arg3 -- int that bank1 needs to be set to
 * Side Effects: Might clear all bits in some cases
 * Error Conditions: None
 * Return Value: None
 */

void clear(unsigned int lightBank[], const unsigned int bank0, const unsigned
    int bank1)
{
    /* store both indexes into different ints */
    int numOne = lightBank[0];
    int numTwo = lightBank[1];
    
    /* make a function call to AND and then XOR the num and the bank */
    lightBank[0] = clearBits(numOne, bank0);
    lightBank[1] = clearBits(numTwo, bank1);

    return;
}

/*
 * Function name: clearBits()
 * Function prototype: static int clearBits(int num, int bank)
 * Description: This function does the main part of clearing bits. It first
 *              ANDs the num and the bank and the XORs the num and the result
 *              from the previous calculation.
 * Parameters:
 *              arg1 -- int num -- integer 1 or 2 from the array
 *              arg2 -- int bank -- integer that is our bank
 * Side Effects: None
 * Error Conditions: None
 * Return Value: Returns the result after clearing the bits
 */
static int clearBits(int num,int bank)
{
    /* we want to get rid of all turned off lights */
    int andedResult = num & bank;

    /* turn off light if it is on */
    int result = num ^ andedResult;
    return result;
}
