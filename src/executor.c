#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

int execute(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
        return 1;

    if (is_builtin(args[0])) {
        run_builtin(args);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("myshell: fork failed");
        return -1;

    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            fprintf(stderr,
                    "myshell: command not found: %s\n",
                    args[0]);
            exit(1);
        }

    } else {
        waitpid(pid, &status, 0);
    }

    return 1;
}

int execute_pipe(char *input)
{
    char *left, *right, *pipe_pos;
    char **args_left, **args_right;
    int fd[2];
    pid_t pid1, pid2;

    pipe_pos = strchr(input, '|');
    if (!pipe_pos) return 0;

    *pipe_pos = '\0';
    left  = input;
    right = pipe_pos + 1;

    args_left  = parse_input(left);
    args_right = parse_input(right);

    if (pipe(fd) == -1) {
        perror("myshell: pipe failed");
        return -1;
    }

    pid1 = fork();
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(args_left[0], args_left);
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(args_right[0], args_right);
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    free(args_left);
    free(args_right);
    return 1;
}
