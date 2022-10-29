#include "../src/bs_lex.h"
#include "../include/acutest.h"


void test_should_identify_single_character_tokens(void) {
    // given
    const char * source = "(){}[],.~:;?";
    bs_lex_init(source);
    
    // when
    bs_token should_left_paren = next_token();
    bs_token should_right_paren = next_token();
    bs_token should_left_brace = next_token();
    bs_token should_right_brace = next_token();
    bs_token should_left_bracket = next_token();
    bs_token should_right_bracket = next_token();
    bs_token should_comma = next_token();
    bs_token should_dot = next_token();
    bs_token should_bit_not = next_token();
    bs_token should_colon = next_token();
    bs_token should_semi_colon = next_token();
    bs_token should_question_mark = next_token();
    bs_token should_eof = next_token();
    
    // then
    TEST_CHECK(should_left_paren.type == TK_LEFT_PAREN);
    TEST_CHECK(should_left_paren.line == 1);
    TEST_CHECK(should_left_paren.length == 1);

    TEST_CHECK(should_right_paren.type == TK_RIGHT_PAREN);
    TEST_CHECK(should_right_paren.line == 1);
    TEST_CHECK(should_right_paren.length == 1);

    TEST_CHECK(should_left_brace.type == TK_LEFT_BRACE);
    TEST_CHECK(should_left_brace.line == 1);
    TEST_CHECK(should_left_brace.length == 1);

    TEST_CHECK(should_right_brace.type == TK_RIGHT_BRACE);
    TEST_CHECK(should_right_brace.line == 1);
    TEST_CHECK(should_right_brace.length == 1);

    TEST_CHECK(should_left_bracket.type == TK_LEFT_BRACKET);
    TEST_CHECK(should_left_bracket.line == 1);
    TEST_CHECK(should_left_bracket.length == 1);

    TEST_CHECK(should_right_bracket.type == TK_RIGHT_BRACKET);
    TEST_CHECK(should_right_bracket.line == 1);
    TEST_CHECK(should_right_bracket.length == 1);

    TEST_CHECK(should_comma.type == TK_COMMA);
    TEST_CHECK(should_comma.line == 1);
    TEST_CHECK(should_comma.length == 1);

    TEST_CHECK(should_dot.type == TK_DOT);
    TEST_CHECK(should_dot.line == 1);
    TEST_CHECK(should_dot.length == 1);

    TEST_CHECK(should_bit_not.type == TK_BIT_NOT);
    TEST_CHECK(should_bit_not.line == 1);
    TEST_CHECK(should_bit_not.length == 1);

    TEST_CHECK(should_colon.type == TK_COLON);
    TEST_CHECK(should_colon.line == 1);
    TEST_CHECK(should_colon.length == 1);

    TEST_CHECK(should_semi_colon.type == TK_SEMICOLON);
    TEST_CHECK(should_semi_colon.line == 1);
    TEST_CHECK(should_semi_colon.length == 1);

    TEST_CHECK(should_question_mark.type == TK_QUESTION_MARK);
    TEST_CHECK(should_question_mark.line == 1);
    TEST_CHECK(should_question_mark.length == 1);
    TEST_CHECK(should_eof.type == TK_EOF);
}

TEST_LIST = {
    {": Should identify '(){}[],.~:;?' as single character tokens", test_should_identify_single_character_tokens},
    {NULL, NULL}
};