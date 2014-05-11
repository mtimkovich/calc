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
