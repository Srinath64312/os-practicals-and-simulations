/*
 * Practical Session 9 (Part 3): Standard Output Redirection using dup2()
 * Redirects file descriptor 1 (STDOUT_FILENO) to output.txt.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;

    /* Open/create output file */
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open output.txt");
        exit(EXIT_FAILURE);
    }

    printf("Before redirection: Output goes to terminal.\n");

    /* Redirect stdout (fd 1) to output.txt */
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2 redirection failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    /* Subsequent standard output writes go to output.txt */
    printf("Hello from redirected standard output!\n");
    printf("This message is stored in output.txt via dup2(fd, STDOUT_FILENO).\n");

    return 0;
}
