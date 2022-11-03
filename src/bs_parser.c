#include "bs_parser.h"


typedef struct {
    bs_token previous;
    bs_token current;
    bool hadError;
    bool panikMode;
} bs_parser;

static void bs_parser_init(bs_parser * parser) {
    
}

static void advance() {

}

static AST * primary() {

} 

static AST * unary() {

}

static AST * factor() {

}

/*
<term> ::= <factor> (("-" | "+") <factor>)* ;
*/
static AST * term() {

}

/*
<comparison> ::= <term> ((">" | "<" | "<=" | ">=") <term>)* ;
*/
static AST * comparison() {
    AST * node = term();
    if (match(TK_GREATER)) {
        return AST_NEW(BINARY_EXPRESSION,
            node,
            AST_NEW(term()),
            operator);
        )
    }
    return node;
}

/*
<equality> ::= <comparison> (("==" | "!=") <comparison>)* ;
*/
static AST * equality() {
    AST * node = comparison();
    if (match(TK_EQUAL_EQUAL)) {
        return AST_NEW(BINARY_EXPRESSION, 
        node, 
        AST_NEW(comparison()),
        operator);
    }
    return node;
}

/*
<expression> ::= <equality> ;
*/
static AST * expression() {
    return equality();
}

AST * parse(const char * source) {
    bs_lex_init(source);


    bs_lex_free(source);
}