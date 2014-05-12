#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "token.h"

void make_number(Token tok, const char* input, int* ptr)
{
    tok->tokentype = NUMBER;
    tok->datatype = INTEGER;

    // Get the length of the number token
    int length = 0;

    while (input[*ptr+length] != '\0' && isdigit(input[*ptr+length])) {
        length++;
    }

    char* buffer = malloc(length+1);
    strncpy(buffer, input + *ptr, length);
    sscanf(buffer, "%d", &tok->intval);

    free(buffer);

    *ptr += length-1;
}

Token tokenize(const char* input)
{
    initsymbols();
    Token list = NULL;
    int i = 0;

    while (input[i] != '\0') {
        Token tok = talloc();

        int c = input[i];

        if (isdigit(c) || c == '.') {
            // TODO: Handle floats
            make_number(tok, input, &i);

            printtoken(tok);
            list = cons(tok, list);
        } else if (optable[c] >= 0) {
            tok->tokentype = OPERATOR;
            tok->datatype = INTEGER;
            tok->whichval = optable[c];
            tok->name = c;

            printtoken(tok);
            list = cons(tok, list);
        } else {
            free(tok);
        }

        i++;
    }

    return list;
}

void reduceop(Token operand_stack, Token op_stack)
{
}

Token parse(Token tokens)
{
    Token op_stack = NULL;
    Token operand_stack = NULL;

    while (tokens != NULL) {
        Token next = tokens->link;

        if (tokens->tokentype == NUMBER) {
            operand_stack = cons(tokens, operand_stack);
        } else if (tokens->tokentype == OPERATOR) {
            op_stack = cons(tokens, op_stack);
        }

        tokens = next;
    }

    while (op_stack != NULL) {
        reduceop(operand_stack, op_stack);
    }

    printf("length: %d\n", length(operand_stack));
    printf("length: %d\n", length(op_stack));

    return NULL;
}

int main()
{
//     char* input;

    for (;;) {
//         input = readline("> ");

//         if (!input || strcmp(input, "exit") == 0) {
//             break;
//         }

        char input[] = "314+2";
//         char input[] = "1+2";

        printf("%s\n", input);
//         printf("size: %zu\n", strlen(input));

        Token tokens = tokenize(input);
        Token tree = parse(tokens);

        add_history(input);

//         free(input);
        break;
    }

    return 0;
}
