/*
 * Practical Session 7: Understanding Linux Process Address Space
 * 
 * Objective:
 * Write a C program that prints the virtual addresses of code, global, static,
 * heap, and stack variables, and analyze the corresponding segments in Linux
 * using /proc/<PID>/maps and pmap.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Global variables */
int global_var = 10;       // Initialized global -> Data segment (.data)
int global_uninit;         // Uninitialized global -> BSS segment (.bss)

/* Function -> Code/Text segment (.text) */
void display_code_address(void) {
    printf("Code / Text address: %p  (Function: display_code_address)\n", (void *)display_code_address);
}

int main(void) {
    /* Static variable */
    static int static_var = 20; // Initialized static -> Data segment

    /* Local variable -> Stack */
    int stack_var = 30;

    /* Dynamic memory -> Heap */
    int *heap_var = (int *)malloc(sizeof(int));
    if (heap_var == NULL) {
        perror("Memory allocation failed");
        return 1;
    }
    *heap_var = 40;

    printf("=================================================================\n");
    printf(" Practical Session 7: Linux Process Address Space Inspection     \n");
    printf("=================================================================\n");
    printf("Process PID: %d\n\n", getpid());

    printf("--- Variable & Function Virtual Addresses ---\n");
    display_code_address();
    printf("Global address     : %p  (Initialized .data)\n", (void *)&global_var);
    printf("Static address     : %p  (Initialized .data)\n", (void *)&static_var);
    printf("BSS address        : %p  (Uninitialized .bss)\n", (void *)&global_uninit);
    printf("Heap address       : %p  (Dynamic heap allocation via malloc)\n", (void *)heap_var);
    printf("Stack address      : %p  (Local variable on stack frame)\n", (void *)&stack_var);
    printf("---------------------------------------------\n\n");

    printf("Virtual Address Hierarchy Analysis:\n");
    printf("  [High Address]  Stack   -> %p (grows downwards)\n", (void *)&stack_var);
    printf("                  Heap    -> %p (grows upwards)\n", (void *)heap_var);
    printf("                  BSS     -> %p\n", (void *)&global_uninit);
    printf("                  Data    -> %p\n", (void *)&global_var);
    printf("  [Low Address]   Text    -> %p (executable instructions)\n\n", (void *)display_code_address);

    printf("To view the active memory mappings in real-time, run in another terminal:\n");
    printf("  cat /proc/%d/maps\n", getpid());
    printf("  pmap %d\n", getpid());
    printf("  grep -E \"VmSize|VmRSS|VmData|VmStk|VmExe\" /proc/%d/status\n\n", getpid());

    printf("Press Enter to release memory and exit...");
    fflush(stdout);
    getchar();

    free(heap_var);
    printf("Heap memory freed. Process exiting.\n");
    return 0;
}
