/*
 * Practical Session 9 (Part 4): Standard Input Redirection using dup2()
 * Redirects file descriptor 0 (STDIN_FILENO) from input.txt.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    char buffer[256];

    /* Open input file */
    fd = open("input.txt", O_RDONLY);
    if (fd == -1) {
        perror("open input.txt failed (ensure input.txt exists)");
        exit(EXIT_FAILURE);
    }

    /* Redirect stdin (fd 0) to input.txt */
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2 redirection failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    /* fgets/scanf now reads directly from input.txt instead of keyboard */
    printf("Reading from redirected standard input:\n");
    printf("----------------------------------------\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("%s", buffer);
    }
    printf("----------------------------------------\n");
    printf("Completed reading redirected standard input.\n");

    return 0;
}
