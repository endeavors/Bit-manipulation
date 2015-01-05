#include "test.h"
#include "pa2.h"
#include <stdio.h>

int
main()
{
    const unsigned int bank0 = 0x60606060;
    const unsigned int bank1 = 0xAAAAAAAA;
    unsigned int array[2] = {0x10101010, 0x10101010};
    set(array,bank0,bank1);/* == {0x90909090, 0xBA});*/
    printf("%x\n",array[0]);
    printf("%x\n", array[1]);
    return 0;
}
