/*
 * Filename: main.c
 * Author: Gurkirat Singh
 * Description: This file takes input from command line or from file
 *              and then performs bit wise operations to clear,shift,set,
 *              toggle, rotate, or ripple bits. This is just turning the lights
 *              on or off.
 */

/* Standard C libraries go first and then local headers */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "strings.h"
#include "pa2.h"

/* global variable to keep track of there was an error with end pointer 
 * when converting string to long */
int ptrError = EINVAL;

/*
 * Function name: main()
 * Function prototype: int main(int argc, char *argc[]);
 * Description: Checks if a file was inputted to get the commands from,and if
 *              not then just asks the user for the input through stdin. It
 *              prints out appropriate error messages and then calls the
 *              command to execute and then display the lights.
 * Paramters:
 *     arg 1 -- int argc -- number of arguments on command line
 *     arg 2 -- char *argv[] -- contains all of the arguments in array
 * Side Effects: Calls different files for each command.
 * Error Conditions: checks for valid input string, if command exists,
 *               or things like if the errno is set or not
 * Return Value: 0 indicating successful execution
 */
int main(int argc, char *argv[])
{
    /* ---------------- Local variables ------------------- */

    /* Turn off buffering in stdout */
    (void) setvbuf(stdout, NULL, _IONBF, 0);
    unsigned int lightBank[NUM_OF_BANKS] = {0,0};

    /* tells you if reading from file or stdin */
    FILE *file;

    /* stores what was inputted */
    char buf[BUFSIZ]; 

    /* for tokenizing strings */
    char *cmdTok, *argOneTok, *argTwoTok;

    /* tells you what command was typed */
    int returnedIndex; 
    const char * const commands[] = {COMMANDS,NULL};
    int prompt;

    /* ----------------------------------------------------- */

    /* There can be no more than 2 arguments; prints usage */
    if (argc > 2){
        (void)fprintf(stderr, STR_USAGE_MSG, argv[0]);
        return 0;
    }

    /* input needs to be taken from stdin, so print out the prompt sign */
    if (argc == 1){
        prompt = TRUE;
        file = stdin;
    }else if (argc == 2){

        /* commands will be taken from file; try to open the file */
        prompt = FALSE;
       file = fopen(argv[1], "r");
    } 

    /* show the first row of lights; all should be turned off */
    displayLights(lightBank);

    /* Run a loop that tokenizes the line inputted and then runs the command
     * according 
     */
    for(DISPLAY_PROMPT; fgets(buf, BUFSIZ,file) != NULL;DISPLAY_PROMPT){

        /* if nothing is returned, display prompt sign again */
        if (*buf == '\n'){
            continue;
        }
        /* create a new char pointer to print out what string was inputted
         * incorrectly
         */
        char charPointer[BUFSIZ];

        /* tokenize inputted line and check if command exists */
        cmdTok = strtok(buf, TOKEN_SEPARATORS); 
        returnedIndex = checkCmd(cmdTok, commands);

        /* Cannot tokenize before checking what is buf */
        if (returnedIndex == -1){
            /* command doesn't exist */
            (void)fprintf(stderr, STR_BAD_CMD);
            continue;

        }else if (returnedIndex == HELP){
            (void)fprintf(stderr,STR_HELP_MSG); 
            continue;

        }else if (returnedIndex == QUIT){
            /* quit the program */
            return 0;
        } 

        /* tokenize the rest of the string */
        argOneTok = strtok(NULL, TOKEN_SEPARATORS);
        argTwoTok = strtok(NULL, TOKEN_SEPARATORS);

        /* first argument was not entered; display error */
        if (argOneTok == NULL){
            (void)fprintf(stderr, STR_ARGS_REQ);
            continue;
        }

        if (returnedIndex == SET || returnedIndex == CLEAR ||
            returnedIndex == TOGGLE){
            
            /* argument 2 was not entered */
            if (argTwoTok == NULL){
                (void)fprintf(stderr, STR_TWO_ARGS_REQ);
                continue;
            }
            
            /* convert string to long int */
            long longNumOne = strToULong(argOneTok,0);

            /* int is not int */
            if (errno == EINVAL){
                (void)fprintf(stderr, STR_STRTOLONG_NOTINT, argOneTok);
                continue;
            }

            /* int is too long */
            if(errno != 0){
                (void)snprintf(charPointer,BUFSIZ,STR_STRTOLONG_CONVERTING,
                    argOneTok,0);
                perror(charPointer);
                continue;
            }

            /* convert the second argument to long int */
            long longNumTwo = strToULong(argTwoTok, 0);

            /* inputted string is not integer */
            if (errno == EINVAL){
                (void)fprintf(stderr, STR_STRTOLONG_NOTINT, argTwoTok);
                continue;
            }
            
            /* errno was set, so integer is longer than size of int */
            if(errno != 0){
                (void)snprintf(charPointer, BUFSIZ, STR_STRTOLONG_CONVERTING,
                    argTwoTok,0);
                perror(charPointer);
                continue;
            }
           
            /* perform command according to which command was entered */
            switch(returnedIndex)
            {
                case SET:
                    set(lightBank, longNumOne, longNumTwo);
                    break;

                case CLEAR:
                    clear(lightBank, longNumOne, longNumTwo);
                    break;

                case TOGGLE:
                    toggle(lightBank,longNumOne,longNumTwo);
                    break;

                default:
                    break;
            }
            /* display the two integers in * or - to represent the light bank */
            displayLights(lightBank);


        }else{
            /* All theses commands in this else statement only take 2 
             * paramters
             */
            long longNumOne = strToULong(argOneTok,0);
            
            /* print error was string was not integer */
            if (errno == EINVAL){
                (void)fprintf(stderr, STR_STRTOLONG_NOTINT, argOneTok);
                continue;

            }

            /* integer is out of size according to size of int */
            if(errno != 0){
                (void)snprintf(charPointer, BUFSIZ, STR_STRTOLONG_CONVERTING, 
                    argOneTok,0);
                perror(charPointer);
                continue;
            }
            
            /* execute command according to the command that was entered
             * and then display the lights
             */
            switch(returnedIndex)
            { 
                case SHIFT:
                    shift(lightBank,longNumOne);
                    displayLights(lightBank);
                    break;
                case ROTATE:
                    rotate(lightBank,longNumOne);
                    displayLights(lightBank);
                    break;

                case RIPPLE:
                    ripple(lightBank,longNumOne);
                    /* This causes ripple to not display the lights twice
                     * since ripple itself is display the lights in its own
                     * file
                     */
                    if (longNumOne == 0){
                        displayLights(lightBank);     
                    }
                    break;

                default:
                    break;
            }

        }

    }

    return 0;
}
