#include <stdio.h>
#include <stdlib.h>

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

void initsymbols()
{
    int i;
    for (i = 0; i < ASCII; i++) {
        optable[ASCII] = -1;
    }

    optable['+'] = PLUSOP;
    optable['-'] = MINUSOP;
    optable['*'] = TIMESOP;
    optable['/'] = DIVIDEOP;
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

