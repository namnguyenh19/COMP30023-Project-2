#include <stdio.h>
#include <assert.h>

#include "uint256.h"

int main (int argc, char **argv) {
    BYTE uint256a[32], uint256b[32], uint256c[32], uint256d[32];
    BYTE clean[32];

    uint256_init (uint256a);
    uint256_init (uint256b);
    uint256_init (uint256c);
    uint256_init (uint256d);
    
    uint256_init (clean);

    uint256a[31] = 0x1;
    uint256b[31] = 0xb;
    uint256d[2] = 0xa;
    uint256d[28] = 0x12;

    printf ("TEST #1: uint256 shift left 0x1 << 9 \n");
    uint256_sl (uint256c, uint256a, 9);
    assert (uint256c[30] == 0x02);
    printf ("TEST #1 PASSED\n");
   
    printf ("TEST #2a: uint256 add 0x1 + 0xb \n");
    uint256_add (uint256c, uint256a, uint256b);
    assert (uint256c[31] == 0xc);

    printf ("TEST #2 PASSED\n");

    printf ("TEST #3a: uint256 mul 0x1 * 0xb\n");
    uint256_mul (clean, uint256a, uint256b);
    assert (clean[31] == 0xb);
   
    uint256_init (clean);  
    
    printf ("TEST #3b: uint256 mul 0x2 * 0xb\n");
    uint256a[31] = 0x2;
    uint256_mul (clean, uint256a, uint256b);
    assert (clean[31] = 0x22);

    uint256_init (clean);    

    printf ("TEST #3c: uint256 mul 0x2 * 0x2\n");
    uint256a[31] = 0x2;
    uint256_mul (clean, uint256a, uint256a);
    assert (clean[31] = 0x4);

    uint256_init (clean);

    printf ("TEST #3d: uint256 mul 0x10 * 0x10\n");
    uint256b[31] = 0x10;
    uint256_mul (clean, uint256b, uint256b);
    assert (clean[30] == 0x01 && clean[31] == 0x00);

    printf ("TEST #3 PASSED\n");

    uint256_init (clean);
    
    printf ("TEST #4a: uint256 exp 0x2 ** 0x2\n");
    uint256_exp (clean, uint256a, 2); 
    assert (clean[31] == 0x4);
    
    uint256_init (clean);

    printf ("TEST #4b: uint256 exp 0x02 ** 0x3f\n");
    uint256_exp (clean, uint256a, 0x3f);
    assert (clean[24] == 0x80);
    printf ("TEST #4 PASSED\n");

    uint256_init (clean);
}
