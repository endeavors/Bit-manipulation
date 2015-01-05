#include "pa2.h"
#include "test.h"

int
main()
{
    unsigned int lightBank[] = {0xFFFF0000, 0x0000FFFF};
    const int shiftcount = -8;

    shift(lightBank, shiftcount);
    TEST( lightBank[0] == 0x00FFFF00);
    TEST( lightBank[1] == 0x000000FF);

    unsigned int lightBank2[] = {0x12341234, 0xFFFFFFFF  };
    const int shiftcount2 = 12;

    shift(lightBank2, shiftcount2);
    TEST(lightBank2[0] == 0x41234FFF);
    TEST(lightBank2[1] == 0xFFFFF000);
  
    unsigned int lightBank3[] = {0x81241279, 0xF9871247};
    const int shiftcount3 = 24;

    shift(lightBank3, shiftcount3);
    TEST(lightBank3[0] == 0x79F98712);
    TEST(lightBank3[1] == 0x47000000);

    unsigned int lightBank4[] = {0x81241279, 0xF9871247};
    const int shiftcount4 = 1;

    shift(lightBank4, shiftcount4);
    TEST(lightBank4[0] == 0x81241279);
    TEST(lightBank4[1] == 0xF9871247);

    printf("%x\n", lightBank4[0]);
    printf("%x\n", lightBank4[1]);

    return 0;

}
