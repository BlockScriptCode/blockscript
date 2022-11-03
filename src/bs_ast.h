#ifndef bs_ast_h
#define bs_ast_h

#include <stdlib.h>
#include "bs.h"
#include "bs_lex.h"

#define OPERATOR_OFFSET 11

#define AST_NEW(type, ...) \
  ast_new((AST){type, {.type=(struct type){__VA_ARGS__}}})
#define AST_DATA(ast, type) \
    (ast->data.type)
#define AS_AST_OPERATOR(token) \
    (token - OPERATOR_OFFSET)
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
    BIT_NOT, 
    BANG,
    MINUS,
    MINUS_MINUS,
    PLUS, 
    PLUS_PLUS,            
    SLASH,                      
    STAR,               
    BIT_AND,               
    BIT_OR,               
    EQUAL_EQUAL,               
    GREATER, 
    BIT_SHIFT_RIGHT,
    GREATER_EQUAL,  
    LESS, 
    BIT_SHIFT_LEFT,
    LESS_EQUAL,
} ast_operator;

typedef struct AST AST;

struct AST {
    // char * start;
    // int length;
    ast_type type;
    union {
        struct INTEGER_LITERAL        {int number;}                                                 INTEGER_LITERAL;
        struct FLOAT_LITERAL          {float number;}                                               FLOAT;
        struct UNARY_EXPRESSION       {AST * argument; ast_operator operator;}                      UNARY_EXPRESSION;
        struct BINARY_EXPRESSION      {AST * left; AST * right; ast_operator operator;}             BINARY_EXPRESSION;
        struct CONDITIONAL_EXPRESSION {AST * test; AST * consequent; AST * alternate;}              CONDITIONAL_EXPRESSION;
        struct EXPRESSION_STATEMENT   {AST * expression;}                                           EXPRESSION_STATEMENT; 
    } data;
};

AST * ast_new(AST ast);
void ast_free(AST *ptr);
void print_ast(AST * ast);

#endif