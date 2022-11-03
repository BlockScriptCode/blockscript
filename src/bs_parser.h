#ifndef bs_parser_h
#define bs_parser_h
#include "bs.h"
#include "bs_ast.h"
#include "bs_lexer.h"
#include "bs_error.h"

AST * parse(const char * source);
#endif



