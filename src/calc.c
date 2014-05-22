#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "token.h"

// Convert the string to an integer token
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

// Convert the input string into Token structs
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

// Reduce the operand and op stack to a tree
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

// Convert the tokens to a tree
Token parse(Token tokens)
{
    Token op_stack = NULL;
    Token operand_stack = NULL;

    while (tokens != NULL) {
        Token next = tokens->link;

        if (tokens->tokentype == NUMBER) {
            operand_stack = cons(tokens, operand_stack);
        } else if (tokens->tokentype == OPERATOR) {
            if (tokens->whichval == LPAREN) {
                op_stack = cons(tokens, op_stack);
            } else if (tokens->whichval == RPAREN) {
                while (op_stack->whichval != LPAREN) {
                    Token rest_op_stack = op_stack->link;
                    operand_stack = reduceop(operand_stack, op_stack);
                    op_stack = rest_op_stack;
                }

                op_stack = op_stack->link;
            } else {
                while (op_stack != NULL && op_stack->whichval != LPAREN && tokens->whichval <= op_stack->whichval) {
                    Token rest_op_stack = op_stack->link;
                    operand_stack = reduceop(operand_stack, op_stack);
                    op_stack = rest_op_stack;
                }

                op_stack = cons(tokens, op_stack);
            }
        }

        // If the token was a parenthesis, free it. The other tokens are reused
        if (tokens->whichval == LPAREN || tokens->whichval == RPAREN) {
            free(tokens);
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

// Do math
int math(Token oper, int a, int b)
{
    switch (oper->name) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
                  if (b == 0) {
                      printf("error: Division by zero.\n");
                      return -1;
                  }

                  return a / b;
        case '%': return a % b;
        case '^': return power(a, b);
        default: return -1;
    }
}

// Evaluate the tree to get a number value
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

//         char input[] = "2*2+2";

//         printf("%s\n", input);

        Token tokens = tokenize(input);
//         pplist(tokens);
        Token tree = parse(tokens);
//         pplist(tree);

        int result = evaluate(tree);

        printf("\n%d\n\n", result);

        add_history(input);

        free_tree(tree);
        free(input);
//         break;
    }

    return 0;
}
