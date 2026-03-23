#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

static char *history[MAX_HISTORY];
static int history_count = 0;

void add_history(char *input)
{
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(input);
    } else {
        free(history[0]);
        int i;
        for (i = 0; i < MAX_HISTORY - 1; i++)
            history[i] = history[i + 1];
        history[MAX_HISTORY - 1] = strdup(input);
    }
}

void show_history(void)
{
    int i;
    if (history_count == 0) {
        printf("No commands in history\n");
        return;
    }
    for (i = 0; i < history_count; i++)
        printf("  %d: %s\n", i + 1, history[i]);
}

int is_builtin(char *cmd)
{
    if (!cmd) return 0;
    return (strcmp(cmd, "cd")      == 0 ||
            strcmp(cmd, "exit")    == 0 ||
            strcmp(cmd, "help")    == 0 ||
            strcmp(cmd, "history") == 0 ||
            strcmp(cmd, "clear")   == 0 ||
            strcmp(cmd, "pwd")     == 0);
}

void run_builtin(char **args)
{
    if (strcmp(args[0], "exit") == 0) {
        printf("Goodbye!\n");
        exit(0);

    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL)
            chdir(getenv("HOME"));
        else {
            if (chdir(args[1]) != 0)
                perror("myshell: cd");
        }

    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[MAX_PATH];
        if (getcwd(cwd, sizeof(cwd)))
            printf("%s\n", cwd);

    } else if (strcmp(args[0], "history") == 0) {
        show_history();

    } else if (strcmp(args[0], "clear") == 0) {
        printf("\033[2J\033[H");

    } else if (strcmp(args[0], "help") == 0) {
        printf("\n");
        printf("MyShell v1.0 - Built-in Commands:\n");
        printf("----------------------------------\n");
        printf("  cd [dir]   - Change directory\n");
        printf("  pwd        - Print current directory\n");
        printf("  history    - Show command history\n");
        printf("  clear      - Clear screen\n");
        printf("  help       - Show this help\n");
        printf("  exit       - Exit shell\n");
        printf("\nAll Linux commands work too!\n");
        printf("Pipes supported: ls | grep .c\n");
        printf("\n");
    }
}
