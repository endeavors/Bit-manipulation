#include "pa2.h"
#include "test.h"

int testclear()
{
    unsigned int lightBank[] = {0x12345678, 0xFFFFFFFF};
    const unsigned int bank0 = 0xFF123F8F;
    const unsigned int bank1 = 0x12890445;

    clear(lightBank,bank0,bank1); 
    if (lightBank[0] == 0x244070){
        printf("%s\n", "PASSED");
    }else{
        printf("%s\n", "FAILED");
    }
    if (lightBank[1] == 0xed76fbba){
        printf("%s\n", "PASSED");
    }else{
        printf("%s\n", "FAILED");
    } 
    unsigned int lightBank1[] = {0x1289F345, 0xABED4561};
    const unsigned int bank2 = 0xDDEADBEE;
    const unsigned int bank3 = 0xDEADFEEB;

    clear(lightBank1, bank2,bank3);
    if (lightBank1[0] == 0x2012001){
        printf("%s\n", "PASSED");
    }else{
        printf("%s\n", "FAILED");
    }

    if (lightBank1[1] == 0x21400100){
        printf("%s\n", "PASSED");
    }else{
        printf("%s\n", "FAILED");
    }

}
int
main()
{
    testclear();
    return 0;
}
