#include <stddef.h>
#include "pa2.h"
#include "test.h"

int checkCmdTest()
{
    const char * array[] = {"set","daddy","what","yo","help","nope",NULL};
    const char  * const s = "daddy";

    const char * comm[] = {COMMANDS, NULL};
    const char * const co = "shift";

    const char * const si = "help";
    const char * const so =  "   ";
    const char * const sh = "what";
    const char * const sy = "yo";

    TEST(checkCmd(co, comm) == 3);
    TEST(checkCmd(co, comm) == 4);
    printf("sh %s\n", comm);

    printf("shfit %s\n",array);
    TEST(checkCmd(s, array) == 1);
    TEST(checkCmd(sh, array) == 2);
    TEST(checkCmd(si,array) == 4);
    TEST(checkCmd(sy, array) != 5);
    TEST(checkCmd(so, array) != 2);
}

int
main()
{
    checkCmdTest();
    return 0;
}
