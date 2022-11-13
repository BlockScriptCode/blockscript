#include "../src/bs_parser.h"
#include "../src/bs_value.h"
#include "../include/acutest.h"

void should_parse_binary_expressions(void) {
    // given
    const char * source = "3 + 4 * 5";
    // when
    AST * ast = parse(source);
    // then
    TEST_CHECK(ast->type == BINARY_EXPRESSION);
    TEST_CHECK(AST_DATA(ast, BINARY_EXPRESSION).operator == PLUS);
    AST * top_left = AST_DATA(ast, BINARY_EXPRESSION).left;
    TEST_CHECK(top_left->type == LITERAL);
    bs_value literal1 = *AST_DATA(top_left, LITERAL).value;
    TEST_CHECK(IS_INT32(literal1));
    TEST_CHECK(AS_INT32_CVAL(literal1) == 3);
    AST * top_right = AST_DATA(ast, BINARY_EXPRESSION).right; 
    TEST_CHECK(top_right->type == BINARY_EXPRESSION);
    TEST_CHECK(AST_DATA(top_right, BINARY_EXPRESSION).operator == STAR);
    AST * left = AST_DATA(top_right, BINARY_EXPRESSION).left;
    bs_value literal2 = *AST_DATA(left, LITERAL).value;
    TEST_CHECK(IS_INT32(literal2));
    TEST_CHECK(AS_INT32_CVAL(literal2) == 4);
    AST * right = AST_DATA(top_right, BINARY_EXPRESSION).right;
    bs_value literal3 = *AST_DATA(right, LITERAL).value;
    TEST_CHECK(IS_INT32(literal3));
    TEST_CHECK(AS_INT32_CVAL(literal3) == 5);
    printf("\n");
    ast_print(ast);
    ast_free(ast);
}

void should_parse_complex_expressions(void) {
    // given
    // TODO post -- ++ doenst work
    const char * source = "3 << 2 & 4 | 5 * ~10";
    // when
    AST * ast = parse(source);
    // then
    TEST_CHECK(ast->type == BINARY_EXPRESSION);
    TEST_CHECK(AST_DATA(ast, BINARY_EXPRESSION).operator == BIT_OR);
    printf("\n");
    ast_print(ast);
    ast_free(ast);
}

void should_parse_expressions(void) {
    // given
    // TODO post -- ++ doenst work
    const char * source = "3";
    // when
    AST * ast = parse(source);
    // then
    // TEST_CHECK(ast->type == BINARY_EXPRESSION);
    // TEST_CHECK(AST_DATA(ast, BINARY_EXPRESSION).operator == BIT_OR);
    printf("\n");
    ast_print(ast);
    ast_free(ast);
}

TEST_LIST = {
    {": Should parse binary expressions", should_parse_binary_expressions},
    {": Should parse complex binary expressions", should_parse_complex_expressions},
    {": Should parse complex binary expressions", should_parse_expressions},
    {NULL, NULL}
};