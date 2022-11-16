#ifndef bs_ast_h
#define bs_ast_h

#include <stdlib.h>
#include "bs.h"
#include "bs_lex.h"
#include "bs_value.h"

#define OPERATOR_OFFSET 11

#define AST_NEW(type, ...) \
    ast_new((AST){type, {.type = (struct type){__VA_ARGS__}}})
#define AST_DATA(ast, type) \
    (ast->data.type)
#define AS_AST_OPERATOR(token) \
    (token - OPERATOR_OFFSET)
typedef enum
{
    // literals
    LITERAL,
    IDENTIFIER,
    // unarys
    UNARY_EXPRESSION,
    // binarys
    BINARY_EXPRESSION,
    // tenary
    CONDITIONAL_EXPRESSION,

    EXPRESSION_STATEMENT,

    VARIABLE_DECLARATOR,
    VARIABLE_DECLARATION,

    BLOCK_STMT,
} ast_type;

typedef enum
{
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

typedef enum
{
    VAR,
    VAL,
} ast_variable_kind;

typedef struct AST AST;

struct AST
{
    ast_type type;
    union
    {
        struct LITERAL
        {
            bs_value *value;
        } LITERAL;
        struct IDENTIFIER
        {
            const char *name;
            int length;
        } IDENTIFIER;
        struct UNARY_EXPRESSION
        {
            AST *argument;
            ast_operator operator;
        } UNARY_EXPRESSION;
        struct BINARY_EXPRESSION
        {
            AST *left;
            AST *right;
            ast_operator operator;
        } BINARY_EXPRESSION;
        struct CONDITIONAL_EXPRESSION
        {
            AST *test;
            AST *consequent;
            AST *alternate;
        } CONDITIONAL_EXPRESSION;
        struct EXPRESSION_STATEMENT
        {
            AST *expression;
        } EXPRESSION_STATEMENT;
        struct VARIABLE_DECLARATOR
        {
            AST *id;
            AST *init;
        } VARIABLE_DECLARATOR;
        struct VARIABLE_DECLARATION
        {
            AST *declaration;
            ast_variable_kind kind;
            bs_value_type type;
        } VARIABLE_DECLARATION;
        struct BLOCK_STMT
        {
            int instructionCount;
            AST **instructions;
        } BLOCK_STMT;
    } data;
};

AST *ast_new(AST ast);
void ast_free(AST *ptr);
void ast_print(AST *ast);

#endif