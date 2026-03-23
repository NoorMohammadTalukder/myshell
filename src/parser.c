#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char **parse_input(char *input)
{
    char **args = malloc(MAX_ARGS * sizeof(char *));
    char *token;
    int i = 0;

    if (!args) {
        fprintf(stderr, "myshell: memory error\n");
        exit(1);
    }

    token = strtok(input, " \t\r\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;

    return args;
}
