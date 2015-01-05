#include <stdlib.h>
#include <errno.h>
#include "pa2.h"
#include "test.h"

int ptrError = EINVAL;

void teststrToULong()
{
    printf("Testing strToULong()\n");

    TEST(strToULong("25", 10) == 25);
    
    TEST(strToULong("1234dbc",10) == 0);

    TEST(strToULong("     ", 10) == 0);
    printf("32.4 is %d\n",strToULong("32.4", 10));

    TEST(strToULong("999999999999999999999",10) == 0);
    TEST(strToULong("10032", 10)== 10032);
    TEST(strToULong("0xFFFF", 16));
    TEST(strToULong("45",8) == 37);
    printf("%d\n",strToULong("32",0));

  return;

}

int main(void)
{
    teststrToULong();
    return 0;
}
