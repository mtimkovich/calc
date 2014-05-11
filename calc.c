#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char* input;

    for (;;) {
        input = readline("> ");

        if (!input) {
            break;
        }

        printf("%s\n", input);
        printf("size: %d\n", strlen(input));

        add_history(input);

        free(input);
    }

    return 0;
}
