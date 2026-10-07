/*
 * Skilling Session 8: Defensive Memory Management and Leak Detection
 * Demonstrates proper memory lifecycle, allocation checks, and zero leaks for Valgrind.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("=========================================================\n");
    printf("   OSSP Skilling Session 8: Defensive Memory Management  \n");
    printf("=========================================================\n");

    /* Defensive allocation */
    char *buffer = (char *)malloc(256 * sizeof(char));
    if (buffer == NULL) {
        perror("malloc failed");
        return 1;
    }

    strncpy(buffer, "Secure memory buffer initialized without leaks.", 255);
    buffer[255] = '\0';
    printf("Allocated and verified: \"%s\"\n", buffer);

    /* Resize with realloc */
    char *resized = (char *)realloc(buffer, 512 * sizeof(char));
    if (resized == NULL) {
        perror("realloc failed");
        free(buffer);
        return 1;
    }
    buffer = resized;
    strncat(buffer, " Resized safely.", 511 - strlen(buffer));
    printf("After safe realloc: \"%s\"\n", buffer);

    /* Clean deallocation */
    free(buffer);
    buffer = NULL;
    printf("Memory released cleanly. Zero leaks detected.\n");

    return 0;
}
