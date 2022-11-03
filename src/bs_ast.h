#ifndef bs_ast_h
#define bs_ast_h

#include <stdlib.h>
#include "bs.h"

#define AST_NEW(type, ...) \
  ast_new((AST){type, {.type=(struct type){__VA_ARGS__}}})
#define AS_INTEGER_LITERAL(ast) \
    (ast->data.INTEGER_LITERAL)
typedef enum {
    // literals
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    // unarys
    UNARY_EXPRESSION,
    // binarys
    BINARY_EXPRESSION,
    // tenary
    CONDITIONAL_EXPRESSION,

    EXPRESSION_STATEMENT,
} ast_type;

typedef enum {
    PLUS,
    PLUS_PLUS,
    MINUS,
    MINUS_MINUS,
    MUL,
    DIV,
    MOD,
    BIT_AND,
    BIT_OR,
    BIT_SHIFT_RIGHT,
    BIT_SHIFT_LEFT,
} ast_operator;

typedef struct AST AST;

struct AST {
    // char * start;
    // int length;
    ast_type type;
    union {
        struct INTEGER_LITERAL        {int number;}                                                 INTEGER_LITERAL;
        struct FLOAT_LITERAL          {float number;}                                               FLOAT;
        struct UNARY_EXPRESSION       {AST * argument; bool prefix; ast_operator operator;}         UNARY_EXPRESSION;
        struct BINARY_EXPRESSION      {AST * left; AST * right; ast_operator operator;}             BINARY_EXPRESSION;
        struct CONDITIONAL_EXPRESSION {AST * test; AST * consequent; AST * alternate;}              CONDITIONAL_EXPRESSION;
        struct EXPRESSION_STATEMENT   {AST * expression;}                                           EXPRESSION_STATEMENT; 
    } data;
};

AST * ast_new(AST ast);
void ast_free(AST *ptr);
void print_ast(AST * ast);

#endif