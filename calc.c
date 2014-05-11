#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "token.h"

Token tokenize(const char* input)
{
    initsymbols();
    Token list = NULL;
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
            list = cons(tok, list);
        } else if (optable[(int) input[c]] >= 0) {
            tok->tokentype = OPERATOR;
            tok->datatype = INTEGER;
            tok->whichval = optable[(int) input[c]];

            printtoken(tok);
            list = cons(tok, list);
        }

        c++;
    }

    return list;
}

int main()
{
//     char* input;

    for (;;) {
//         input = readline("> ");

//         if (!input || strcmp(input, "exit") == 0) {
//             break;
//         }

//         char input[] = "3.14+2";
        char input[] = "1+2";

        printf("%s\n", input);
        printf("size: %zu\n", strlen(input));

        Token tokens = tokenize(input);
        printf("%d\n", length(tokens));

        add_history(input);

//         free(input);
        break;
    }

    return 0;
}
