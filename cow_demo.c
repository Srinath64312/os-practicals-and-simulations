/*
 * Practical Session 8 (Part 2): Demonstrating Copy-on-Write (COW) After fork()
 *
 * Objective:
 * Allocate a large memory region (100 MB), initialize it, call fork(), and
 * observe memory behavior before and after child modifies shared pages.
 * Modifying 1 byte per 4096-byte page triggers COW page faults, forcing physical
 * page replication only for modified pages.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE (100 * 1024 * 1024)   // 100 MB buffer
#define PAGE_SIZE 4096             // Standard Linux 4 KB page size

static void wait_for_user(const char *prompt) {
    printf("%s", prompt);
    fflush(stdout);
    if (isatty(STDIN_FILENO)) {
        getchar();
    } else {
        printf(" [Auto-advancing in automated environment]\n");
    }
}

int main(void) {
    char *data;

    printf("=================================================================\n");
    printf(" Practical Session 8: Copy-On-Write (COW) Memory Demonstration  \n");
    printf("=================================================================\n");

    /* Allocate 100 MB */
    data = (char *)malloc(SIZE);
    if (data == NULL) {
        perror("malloc 100MB failed");
        return 1;
    }

    /* Initialize memory */
    for (size_t i = 0; i < SIZE; i++) {
        data[i] = 1;
    }

    printf("Parent PID: %d\n", getpid());
    printf("Allocated and initialized 100 MB (%zu bytes) in parent.\n", (size_t)SIZE);
    wait_for_user("Press Enter to perform fork()...");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        free(data);
        return 1;
    }

    if (pid == 0) {
        /* Child process */
        printf("\n[Child Process] PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("[Child Process] Inherited virtual mapping from parent.\n");
        printf("[Child Process] Physical memory is currently SHARED via Copy-on-Write.\n");
        wait_for_user("[Child Process] Press Enter before modifying memory...");

        /*
         * Modify one byte in every page (every 4096 bytes).
         * This triggers write page faults and forces COW page duplication.
         */
        size_t pages_touched = 0;
        for (size_t i = 0; i < SIZE; i += PAGE_SIZE) {
            data[i] = 2;
            pages_touched++;
        }

        printf("[Child Process] Modified 1 byte in each of %zu pages (%zu KB total).\n",
               pages_touched, (pages_touched * PAGE_SIZE) / 1024);
        printf("[Child Process] Private physical pages allocated via COW page faults.\n");
        wait_for_user("[Child Process] Press Enter to finish child process...");

        free(data);
        return 0;
    } else {
        /* Parent process */
        printf("\n[Parent Process] Spawned Child PID: %d\n", pid);
        printf("[Parent Process] Initial physical pages shared with child.\n");
        wait_for_user("[Parent Process] Press Enter to allow child to execute and wait for termination...");

        wait(NULL);
        printf("\n[Parent Process] Child has exited cleanly.\n");
        printf("[Parent Process] Parent's data remains unmodified: data[0] = %d\n", data[0]);

        free(data);
        printf("[Parent Process] Memory freed. Demonstration complete.\n");
    }

    return 0;
}
