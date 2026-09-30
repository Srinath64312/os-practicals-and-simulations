/*
 * Skilling Session 7: Shell Pipeline Architecture using pipe() and dup2()
 * Milestone: Support two-stage pipeline execution (cmd1 | cmd2) with I/O redirection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 32

static void tokenize(char *str, char **argv) {
    int i = 0;
    char *token = strtok(str, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[i] = NULL;
}

static void execute_pipeline(char **cmd1, char **cmd2) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe creation failed");
        return;
    }

    /* Child 1: executes cmd1 and writes stdout to pipe */
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork stage 1 failed");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid1 == 0) {
        close(pipefd[0]); // Unused read end
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 stdout redirection failed");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        execvp(cmd1[0], cmd1);
        perror("execvp cmd1 failed");
        exit(EXIT_FAILURE);
    }

    /* Child 2: executes cmd2 and reads stdin from pipe */
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork stage 2 failed");
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, NULL, 0);
        return;
    }

    if (pid2 == 0) {
        close(pipefd[1]); // Unused write end
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 stdin redirection failed");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        execvp(cmd2[0], cmd2);
        perror("execvp cmd2 failed");
        exit(EXIT_FAILURE);
    }

    /* Parent closes both pipe descriptors so EOF is delivered cleanly */
    close(pipefd[0]);
    close(pipefd[1]);

    /* Wait for both processes in pipeline */
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(void) {
    char input[512];

    printf("=========================================================\n");
    printf("  OSSP Skilling Session 7: Shell Pipeline IPC (pipe & dup2)\n");
    printf("=========================================================\n");
    printf("Supports pipelines e.g.:\n");
    printf("  ls | wc\n");
    printf("  ps -ef | grep bash\n");
    printf("Type 'exit' to quit.\n\n");

    while (1) {
        printf("skilling7> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) break;
        if (strlen(input) == 0) continue;

        if (strchr(input, '|') != NULL) {
            char *argv1[MAX_ARGS];
            char *argv2[MAX_ARGS];

            char *left = strtok(input, "|");
            char *right = strtok(NULL, "|");

            if (!left || !right) {
                printf("[-] Invalid pipeline syntax\n");
                continue;
            }

            tokenize(left, argv1);
            tokenize(right, argv2);

            if (!argv1[0] || !argv2[0]) {
                printf("[-] Missing command in pipeline\n");
                continue;
            }

            execute_pipeline(argv1, argv2);
        } else {
            char *args[MAX_ARGS];
            tokenize(input, args);
            if (!args[0]) continue;

            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                waitpid(pid, NULL, 0);
            } else {
                perror("fork failed");
            }
        }
    }

    printf("Session terminated.\n");
    return 0;
}
