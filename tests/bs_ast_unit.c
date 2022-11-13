#include "../src/bs_ast.h"
#include "../src/bs_value.h"
#include "../include/acutest.h"

void should_generate_ast(void) {
    // given
    AST * ast = AST_NEW(EXPRESSION_STATEMENT,
      AST_NEW(LITERAL, BS_VALUE(BS_INT8, 10))
    );
    // when

    // then
    TEST_CHECK(ast->type == EXPRESSION_STATEMENT);
    TEST_CHECK(ast->data.EXPRESSION_STATEMENT.expression->type == LITERAL);
    bs_value literal = *AST_DATA(ast->data.EXPRESSION_STATEMENT.expression, LITERAL).value;
    TEST_CHECK(IS_INT8(literal));
    TEST_CHECK(AS_INT8_CVAL(literal) == 10);

    ast_free(ast);
}

TEST_LIST = {
    {": Should generate ast", should_generate_ast},
    {NULL, NULL}
};