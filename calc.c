#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "token.h"

Token gentree(const char* input)
{
    initsymbols();
    Token tree;

    Token num_stack = NULL;
    Token op_stack = NULL;
    int c = 0;

    while (input[c] != '\0') {
        Token tok = talloc();

        if (isdigit(input[c])) {
            // TODO: Make this handle numbers that are not one digit
            // e.g. long numbers and decimals
            tok->tokentype = NUMBER;
            tok->datatype = INTEGER;
            tok->intval = input[c] - '0';

            printtoken(tok);
            num_stack = cons(tok, num_stack);
        } else if (optable[c] >= 0) {
            tok->tokentype = OPERATOR;
            tok->datatype = INTEGER;
            tok->whichval = optable[c];

            printtoken(tok);
            op_stack = cons(tok, op_stack);
        }

        c++;
    }

    printf("length of num_stack: %d\n", length(num_stack));
    printf("length of op_stack: %d\n", length(op_stack));

    return tree;
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
