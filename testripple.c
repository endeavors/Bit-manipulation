/*
 * Unit Test for rotate.s
 *
 * void rotate( unsigned int mask[], int rotateCnt );
 *
 * Takes mask[0] as high order 32 bits and mask[1] as low order 32 bits
 * and simulates a 64-bit rotate within these two words.
 *
 * Lower 6 bits of rotateCnt is masked to keep rotate range 0-63.
 *
 * Positive rotateCnt - rotate left
 * Negative rotateCnt - rotate right
 */

#include "test.h"       /* For TEST() macro and stdio.h */
#include <stdlib.h>     /* For rand() function prototype */
#include <limits.h>     /* For LONG_MIN and LONG_MAX */
#include "pa2.h"        /* For rotate() function prototype */

void
testrotate()
{
    unsigned int mask[2];
    unsigned int mask1[2];
    int savedRotateCnt;

    printf( "Testing rotate()\n" );

    /*
     * Test with rotateCnt of 0 - should be no change.
     */
    mask[0] = 0x01234567;
    mask[1] = 0x89ABCDEF;

    ripple( mask, 0 );
    TEST( mask[0] == 0x01234567 && mask[1] == 0x89ABCDEF );

    /*
     * Test masking of lower 6 bits of rotateCnt.
     */

    /* Test with rotateCnt of 64 - should be no change. */
    mask[0] = 0x01234567;
    mask[1] = 0x89ABCDEF;

    ripple( mask, 64 );
    printf("Value is 0x1234567 = %x\n", mask[0]);
    printf("Value is 0x89ABCDEF = %x\n", mask[1]);
    TEST( mask[0] == 0x01234567 );
    TEST( mask[1] == 0x89ABCDEF );

    /* Test with rotateCnt of -64 - should be no change. */
    /* This also tests negating rotateCnt before masking lower 6 bits. */
    mask[0] = 0x01234567;
    mask[1] = 0x89ABCDEF;

    ripple( mask, -64 );
    TEST( mask[0] == 0x01234567 );
    TEST( mask[1] == 0x89ABCDEF );

    /*
     * Test rotating left 1 bit.
     */

    /* Test with bits to rotate being 0 */
    mask[0] = 0x7FFFFFFF;
    mask[1] = 0x7FFFFFFF;

    ripple ( mask, 1 );
    TEST( mask[0] == 0xFFFFFFFE );
    TEST( mask[1] == 0xFFFFFFFE );

    /* Test with bits to rotate being 1 */
    mask[0] = 0x80000000;
    mask[1] = 0x80000000;

    ripple ( mask, 1 );
    TEST( mask[0] == 0x00000001 );
    TEST( mask[1] == 0x00000001 );

    /*
     * Test rotating right 1 bit.
     */

    /* Test with bits to rotate being 0 */
    mask[0] = 0xFFFFFFFE;
    mask[1] = 0xFFFFFFFE;

    ripple ( mask, -1 );
    TEST( mask[0] == 0x7FFFFFFF );
    TEST( mask[1] == 0x7FFFFFFF );

    /* Test with bits to rotate being 1 */
    mask[0] = 0x00000001;
    mask[1] = 0x00000001;

    ripple ( mask, -1 );
    TEST( mask[0] == 0x80000000 );
    TEST( mask[1] == 0x80000000 );

    /*
     * Test with rotateCnt > 64 and < -64
     */

    /* Test with rotateCnt of 65 - should rotate left 1 bit. */
    mask[0] = 0x08080808;
    mask[1] = 0x11111111;

    ripple( mask, 65 );
    TEST( mask[0] == 0x10101010 );
    TEST( mask[1] == 0x22222222 );

    /* Test with rotateCnt of -65 - should rotate right 1 bit. */
    /* This also tests negating rotateCnt before masking lower 6 bits. */
    mask[0] = 0x08080808;
    mask[1] = 0x11111111;

    ripple( mask, -65 );
    TEST( mask[0] == 0x84040404 );
    TEST( mask[1] == 0x08888888 );

    /*
     * Test various # of bits rotate left then right and vice versa
     *   - should end up with original
     */

    mask[0] = 0x01234567;
    mask[1] = 0x89ABCDEF;

    ripple( mask, 2 );
    ripple( mask, -2 );
    TEST( mask[0] == 0x01234567 );
    TEST( mask[1] == 0x89ABCDEF );


    mask[0] = 0x89ABCDEF;
    mask[1] = 0x01234567;

    ripple( mask, -17 );
    ripple( mask, 17 );
    TEST( mask[0] == 0x89ABCDEF );
    TEST( mask[1] == 0x01234567 );

    /*
     * Test random values; rotating one way and then the opposite way
     *   calculated by -(64 - rotateCnt) should give us the same values.
     * For example, rotating +34 should be the same as rotating -30.
     */

    mask[0] = mask1[0] = rand();
    mask[1] = mask1[1] = rand();

    savedRotateCnt = rand();

    ripple( mask, savedRotateCnt );
    ripple( mask1, -(64 - (savedRotateCnt % 64)) );

    TEST( mask[0] == mask1[0] );
    TEST( mask[1] == mask1[1] );

    printf( "Finished running tests on rotate()\n" );

}

int
main()
{
    testrotate();

    return 0;
}
