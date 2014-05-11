#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

Token talloc()
{
    Token tok = (Token) calloc(1, sizeof(struct tokn));

    if (tok == NULL) {
        printf("talloc failed\n");
    }

    return tok;
}

void printtoken(Token tok)
{
    if (tok->tokentype == NUMBER) {
        printf("type: %d\top: %d\tval: %d\n", tok->tokentype, tok->datatype, tok->intval);
    } else if (tok->tokentype == OPERATOR) {
        printf("type: %d\top: %d\tval: %d\n", tok->tokentype, tok->datatype, tok->whichval);
    }
}

char operators[] = "+-*/()";

void initsymbols()
{
    int i;
    for (i = 0; i < ASCII; i++) {
        // Default non-matches to -1
        optable[i] = -1;
    }

    for (i = 0; i < strlen(operators); i++) {
        // The order in operators corresponds to the
        // order in the enum, which is why this works
        optable[(int) operators[i]] = i;
    }
}

Token cons(Token item, Token list)
{
    item->link = list;
    return item;
}

int length(Token list)
{
    if (list == NULL) {
        return 0;
    } else {
        return 1 + length(list->link);
    }
}

