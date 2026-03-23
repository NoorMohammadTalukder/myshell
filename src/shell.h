#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT     1024
#define MAX_ARGS      64
#define MAX_HISTORY   10
#define MAX_PATH      256

void shell_loop(void);
char *read_input(void);
char **parse_input(char *input);
int execute(char **args);
int execute_pipe(char *input);
void run_builtin(char **args);
int is_builtin(char *cmd);
void add_history(char *input);
void show_history(void);
void show_prompt(void);

#endif
