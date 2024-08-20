/*********************************************************************************/
/* Part of the coding for mental health and stress relief series. Just have fun. */
/*********************************************************************************/


#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** 0 - Compile no debugging or printing code.
** 1 - Print out all the prime number.
** 2 - Only print out the largest prime number. Used to check correctness between versions.
 */
#define DEBUG 0

/*
 * No this is not optimus prime, but just a simple way to generate out prime numbers until a certain limit.
 * Also this is the first time I am coding in C after a very long time, so I am a bit rusty. But like they say,
 * or rather I say, rusty nails still can get the job done. So here is to a rusty nail, getting the job done.
 *
 * The first version is always simple. But to make this more robust I want to start making this a bit more optimized.
 * Also I will be removing the print statement for doing the actual benchmarking.
 * I will use N = 1000000000 as a number to calculate the prime numbers upto.
 * 1. Simple version
 *  a. takes 7.255 seconds.
 *  b. Largest prime calculated is - 999999937
 * 2. Version where we do early stopping at the sqrt of the max number.
 *  a. takes 7.171 seconds (almost the same as the simple / normal version)
 *  b. Largest prime cacluated is - 999999937
 * 3. Skip all even numbers (except 2) since every even number after that cannot be a prime number.
 */

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Error. Pass an arugment till which to calculate the prime number\n");
        return 0;
    }

    int maxNumber = atoi(argv[1]);
    int bufferSize = -1;  /* This will store how big the buffer needs to be. */
    /* How many odd numbers are there from 1...maxNumber. We also don't need 1 and 2 to be stored, so let's go ahead and remove that with -2.
     * But we want to keep the last element of bufferSize as well, so lets go ahead and add a +1 to this.
     */
    bufferSize = ceil(maxNumber / 2.0) - 2 + 1;

    /* Let us allocated a simple uint8 array of maxNumber elements, each will either hold a 1 or a 0. */
    uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t) * bufferSize);
    if(buffer == NULL) {
        /* Opps we tried to hard and there is no space left anymore. */
        printf("Tried too hard, cannot allocate that much space. Try a smaller number to calculate all the primes upto\n");
        return 0;
    }

    /* Set everything in buffer to 0 first. This will mean that it has been untouched. */
    memset(buffer, 0x0, bufferSize);

    for(int a=2; a < sqrt(bufferSize); a++) {
        if(buffer[a]) { /* I guess someone already marked this as a multiple */
            continue;
        }
        for(int b=a; a * b < bufferSize; b++) {
            buffer[a*b] = 0x1;
        }
    }

    /* Now that we have made a pass of those loops we can go ahead print out everything that still has a 0 remaining. */
    #if DEBUG == 1
    for(int a=2; a < bufferSize; a++) {
        if(!buffer[a])
            printf("%d,", a);
    }
    #endif // DEBUG

    /* Only print out the largest prime number. */
    #if DEBUG == 2
    for(int a=bufferSize - 1; a > 0; a --) {
        if(!buffer[a]) {
            printf("%d\n", a);
            break;
        }
    }
    #endif

    /* Let us be nice citizens and go ahead and free up the memory resources we made use of */
    free(buffer);

    return 1;
}
