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
        printf("type: %d\top: %d\tval: %c\n", tok->tokentype, tok->datatype, tok->name);
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

Token nreverse_aux(Token list, Token output)
{
    if (list == NULL) {
        return output;
    } else {
        Token first = list;
        Token rest = list->link;
        return nreverse_aux(rest, cons(first, output));
    }
}

Token nreverse(Token list)
{
    return nreverse_aux(list, NULL);
}

Token op(Token tok) {
    return tok;
}

Token lhs(Token tok) {
    return tok->operands;
}

Token rhs(Token tok) {
    return tok->operands->link;
}

void printelem(Token tok)
{
    if (tok->tokentype == NUMBER) {
        printf("%d ", tok->intval);
    } else if (tok->tokentype == OPERATOR) {
        printf("%c ", tok->name);
    }
}

void pplist_aux(Token tree)
{
    printelem(tree);

    if (tree->operands != NULL || tree->link != NULL) {
        if (tree->operands != NULL) {
            pplist_aux(tree->operands);
        }

        if (tree->link != NULL) {
            pplist_aux(tree->link);
        }
    }
}

void pplist(Token tree)
{
    pplist_aux(tree);
    printf("\n");
}
