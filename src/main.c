#include <stdio.h>
#include "shell.h"

int main(void)
{
    printf("\n");
    printf("=============================\n");
    printf("   Welcome to MyShell v1.0   \n");
    printf("   Type 'help' for commands  \n");
    printf("=============================\n");
    printf("\n");

    shell_loop();

    return 0;
}
