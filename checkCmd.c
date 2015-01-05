/*
 * Filename: checkCmd.c
 * Author: Gurkirat Singh
 * Description:Checks if the inputted string paramter is in inside the passed
 *             in char pointer array. Returns -1 if string was not found,else
 *             the index where the string was found in array.
 */

#include <stddef.h>
#include <string.h>
#include "pa2.h"

/*
 * Function name: checkCmd()
 * Function prototype:
 *    int checkCmd(const char * const cmdString, const char* const commands[]);
 * Description: 
 * Parameters:
 *    arg1: const char * const cmdString -- pointer to a first char in "string"
 *            which is basically the string that we need to find inside array
 *    arg2: const char * const commands -- array of char pointers that has
 *            the strings we need to match against the cmdString
 * Side Effects: The last index of the array has to be NULL
 * Error Conditions: array cannot be null for the loop to begin
 * Return Value: -1 if string not found in array, else return the index at
 *            which the string was found in the array
 */

int checkCmd(const char * const cmdString, const char * const commands[])
{
    int index;

    /* Begin the loop as long as array is not null and end it on the same
     * condition
     */
    for (index = 0; commands[index] != NULL ; index++){
        
        /* check if the two strings are the same; if yes, then return the 
         * index the string was found in the array
         */
        if (strcmp(cmdString, commands[index]) == 0){
            return index;
        }
    }

    /* only gets here if cmdString was not found in the array */
    return -1; 

}
