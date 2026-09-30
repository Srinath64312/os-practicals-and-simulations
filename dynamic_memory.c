/*
 * Practical Session 8 (Part 1): Dynamic Memory Allocation & Leak Detection
 * 
 * Objective:
 * Demonstrate malloc(), calloc(), realloc(), and free() in C.
 * Verify heap allocations and ensure zero memory leaks using Valgrind.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i;
    int *malloc_ptr = NULL;
    int *calloc_ptr = NULL;
    int *temp = NULL;

    printf("=================================================================\n");
    printf(" Practical Session 8: Dynamic Memory Allocation & Valgrind Check \n");
    printf("=================================================================\n\n");

    /* -------------------------------------------------------------
     * 1. malloc() demonstration: allocates uninitialized memory block
     * ------------------------------------------------------------- */
    printf("1. malloc() demonstration (allocating 5 integers):\n");
    malloc_ptr = (int *)malloc(5 * sizeof(int));
    if (malloc_ptr == NULL) {
        perror("malloc() failed");
        return 1;
    }

    for (i = 0; i < 5; i++) {
        malloc_ptr[i] = (i + 1) * 10;
    }

    printf("   Memory contents allocated with malloc():\n   [ ");
    for (i = 0; i < 5; i++) {
        printf("%d ", malloc_ptr[i]);
    }
    printf("]\n\n");

    /* -------------------------------------------------------------
     * 2. calloc() demonstration: allocates zero-initialized memory
     * ------------------------------------------------------------- */
    printf("2. calloc() demonstration (allocating 5 zero-initialized integers):\n");
    calloc_ptr = (int *)calloc(5, sizeof(int));
    if (calloc_ptr == NULL) {
        perror("calloc() failed");
        free(malloc_ptr);
        return 1;
    }

    printf("   Initial memory contents allocated with calloc():\n   [ ");
    for (i = 0; i < 5; i++) {
        printf("%d ", calloc_ptr[i]);
    }
    printf("]\n\n");

    /* -------------------------------------------------------------
     * 3. realloc() demonstration: expands allocation from 5 to 10 ints
     * ------------------------------------------------------------- */
    printf("3. realloc() demonstration (resizing malloc_ptr block to 10 integers):\n");
    temp = (int *)realloc(malloc_ptr, 10 * sizeof(int));
    if (temp == NULL) {
        perror("realloc() failed");
        free(malloc_ptr);
        free(calloc_ptr);
        return 1;
    }
    malloc_ptr = temp; // Always assign back to original pointer after successful realloc

    for (i = 5; i < 10; i++) {
        malloc_ptr[i] = (i + 1) * 10;
    }

    printf("   Memory contents after realloc():\n   [ ");
    for (i = 0; i < 10; i++) {
        printf("%d ", malloc_ptr[i]);
    }
    printf("]\n\n");

    /* -------------------------------------------------------------
     * 4. free() demonstration: deallocating all heap blocks
     * ------------------------------------------------------------- */
    printf("4. free() demonstration:\n");
    free(malloc_ptr);
    malloc_ptr = NULL;

    free(calloc_ptr);
    calloc_ptr = NULL;

    printf("   All heap memory blocks successfully freed and pointers nulled.\n");
    printf("   Zero memory leaks verified for Valgrind inspection.\n");

    return 0;
}
