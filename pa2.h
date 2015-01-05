#ifndef PA2_H	/* Macro Guard */
#define PA2_H

/*
 * Local function prototypes for PA2 written in C
 */

int checkCmd( const char * const cmdString, const char * const commands[] );
/*
 * Local function prototypes for PA2 written in Assembly
 */

unsigned long strToULong( const char* str, const int base );
void displayLights( const unsigned int lightBank[] );
void set( unsigned int lightBank[], const unsigned int bank0,
				    const unsigned int bank1 );
void clear( unsigned int lightBank[], const unsigned int bank0,
				      const unsigned int bank1 );
void toggle( unsigned int lightBank[], const unsigned int bank0,
				       const unsigned int bank1 );
void shift( unsigned int lightBank[], const int shiftCnt );
void rotate( unsigned int lightBank[], const int rotateCnt );
void ripple( unsigned int lightBank[], const int rippleCnt );

/*
 * void printChar( const char ch );
 *
 * Only called from an Assembly routine. Not called from any C routine.
 * Would get a lint message about function declared but not used.
 */

#define SET		0
#define CLEAR		1
#define TOGGLE		2
#define SHIFT		3
#define ROTATE		4
#define RIPPLE		5
#define HELP		6
#define QUIT		7

#define SET_CMD		"set"
#define CLEAR_CMD	"clear"
#define TOGGLE_CMD	"toggle"
#define SHIFT_CMD	"shift"
#define ROTATE_CMD	"rotate"
#define RIPPLE_CMD	"ripple"
#define HELP_CMD	"help"
#define QUIT_CMD	"quit"

/*
 * Map the commands strings to indexes for easy association when parsing
 * the commands string to the command.
 */

#define COMMANDS SET_CMD, CLEAR_CMD, TOGGLE_CMD, SHIFT_CMD, ROTATE_CMD, \
	         RIPPLE_CMD, HELP_CMD, QUIT_CMD

#define FALSE 0
#define TRUE 1

/*
 * The prompt to display if we are reading commands interactively from
 * the user vs. reading commands from a file.
 */

#define PROMPT "> "

/*
 * We do this to make it convenient to determine whether to display
 * a prompt or not depending on whether we are reading from stdin or
 * a file.
 */

#define DISPLAY_PROMPT ( (prompt != FALSE) ? (void) printf( PROMPT ) : (void)0 )

#define TOKEN_SEPARATORS " \t\n"

/*
 * Number of banks with 32 lights in each bank.
 */

#define NUM_OF_BANKS 2

#endif /* PA2_H */
