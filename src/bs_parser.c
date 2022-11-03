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

static AST* parse_number_literal() {

}



AST * parse(const char * source) {
    bs_lex_init(source);


    bs_lex_free(source);
}