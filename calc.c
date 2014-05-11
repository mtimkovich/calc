#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "token.h"

Token gentree(const char* input)
{
    Token tok = talloc();
    tok->datatype = OPERATOR;

    return tok;
}

int main()
{
    char* input;

    for (;;) {
//         input = readline("> ");

//         if (!input || strcmp(input, "exit") == 0) {
//             break;
//         }

        input = malloc(4);
        strncpy(input, "1+2", 4);

        printf("%s\n", input);
        printf("size: %zu\n", strlen(input));

        gentree(input);

        add_history(input);

        free(input);
        break;
    }

    return 0;
}
