#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

void show_prompt(void)
{
    char cwd[MAX_PATH];
    getcwd(cwd, sizeof(cwd));
    printf("\033[1;32mmyshell\033[0m:\033[1;34m%s\033[0m$ ",
           cwd);
    fflush(stdout);
}

char *read_input(void)
{
    char *input = malloc(MAX_INPUT);
    if (!input) {
        fprintf(stderr, "myshell: memory error\n");
        exit(1);
    }

    if (!fgets(input, MAX_INPUT, stdin)) {
        free(input);
        return NULL;
    }

    input[strcspn(input, "\n")] = '\0';
    return input;
}

void shell_loop(void)
{
    char *input;
    char **args;

    while (1) {
        show_prompt();

        input = read_input();
        if (!input) break;

        if (strlen(input) == 0) {
            free(input);
            continue;
        }

        add_history(input);

        if (strchr(input, '|')) {
            execute_pipe(input);
        } else {
            args = parse_input(input);
            execute(args);
            free(args);
        }

        free(input);
    }
}
