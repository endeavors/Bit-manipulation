#ifndef STRINGS_H
#define STRINGS_H

/* Use these strings with fprintf to stderr*/
#define STR_STRTOLONG_NOTINT "\n\t\"%s\" is not an integer\n\n"

#define STR_USAGE_MSG "\n\tUsage: %s [filename]\n\n"

#define STR_BAD_CMD "\n\tBad command. Type \"help\" for more info.\n\n"

#define STR_HELP_MSG "The available commands are:\n"\
  "\tset    bank0BitPattern bank1BitPattern\n"\
  "\tclear  bank0BitPattern bank1BitPattern\n"\
  "\ttoggle bank0BitPattern bank1BitPattern\n"\
  "\tshift  shiftCount\n"\
  "\trotate rotateCount\n"\
  "\tripple rippleCount\n"\
  "\thelp\n"\
  "\tquit\n"

#define STR_ARGS_REQ "\n\tArgument(s) required for this command. "\
                     "Type \"help\" for more info.\n\n"
#define STR_TWO_ARGS_REQ "\n\tA 2nd argument is required for this command.\n\n"

/* Use these strings with perror */
#define STR_STRTOLONG_CONVERTING "\n\tConverting \"%s\" base \"%d\""

#endif //STRINGS_H
