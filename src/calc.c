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

            list = cons(tok, list);
        } else if (optable[c] >= 0) {
            tok->tokentype = OPERATOR;
            tok->datatype = INTEGER;
            tok->whichval = optable[c];
            tok->name = c;

            list = cons(tok, list);
        } else {
            free(tok);
        }

        i++;
    }

    // Reverse so the tokens are in order
    return nreverse(list);
}

Token reduceop(Token operand_stack, Token op_stack)
{
    Token rhs = operand_stack;
    Token lhs = rhs->link;
    operand_stack = lhs->link;
    
    Token op = op_stack;

    op->operands = lhs;
    lhs->link = rhs;
    rhs->link = NULL;

    return cons(op, operand_stack);
}

Token parse(Token tokens)
{
    // TODO: Operator precedence and parenthesis
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
        Token rest_op_stack = op_stack->link;
        operand_stack = reduceop(operand_stack, op_stack);
        op_stack = rest_op_stack;
    }

    return operand_stack;
}

int power(int a, int b)
{
    if (b == 0) {
        return 1;
    } else if (b == 1) {
        return a;
    } else if (b > 0) {
        return a * power(a, b-1);
    }

    return 0;
}

int math(Token oper, int a, int b)
{
    switch (oper->name) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return power(a, b);
        default: return -1;
    }
}

int evaluate(Token expr)
{
    if (expr->operands != NULL) {
        int a = evaluate(lhs(expr));
        int b = evaluate(rhs(expr));

        return math(op(expr), a, b);
    } else {
        return expr->intval;
    }
}

int main()
{
    char* input;

    for (;;) {
        input = readline("> ");

        if (!input || strcmp(input, "exit") == 0) {
            break;
        }

//         char input[] = "314+2";
//         char input[] = "1*2+3";
//         char input[] = "1+2";

//         printf("%s\n", input);

        Token tokens = tokenize(input);
//         pplist(tokens);
        Token tree = parse(tokens);
//         pplist(tree);

        int result = evaluate(tree);

        printf("\n%d\n\n", result);

        add_history(input);

        free(input);
//         break;
    }

    return 0;
}
