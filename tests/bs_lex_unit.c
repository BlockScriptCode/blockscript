#include "../src/bs_lex.h"
#include "../include/acutest.h"


void should_identify_single_character_tokens(void) {
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

    bs_lex_free();
}

void should_increment_line_number_with_comments(void) {
    // given
    const char * source = "/*This is a \n multi line \n comment*/\n(\n//Comment\n)";
    bs_lex_init(source);

    // when
    bs_token should_left_paren = next_token();
    bs_token should_right_paren = next_token();
    bs_token should_eof = next_token();

    // then
    TEST_CHECK(should_left_paren.type == TK_LEFT_PAREN);
    TEST_CHECK(should_left_paren.line == 4);
    TEST_CHECK(should_left_paren.length == 1);

    TEST_CHECK(should_right_paren.type == TK_RIGHT_PAREN);
    TEST_CHECK(should_right_paren.line == 6);
    TEST_CHECK(should_left_paren.length == 1);

    TEST_CHECK(should_eof.type == TK_EOF);
    bs_lex_free();
}

void should_identify_single_or_double_character_minus_tokens(void) {
    // given
    const char * source = "- -= --";
    bs_lex_init(source);

    // when
    bs_token should_minus = next_token();
    bs_token should_minus_equal = next_token();
    bs_token should_minus_minus = next_token();
    bs_token should_eof = next_token();

    // then
    TEST_CHECK(should_minus.type == TK_MINUS);
    TEST_CHECK(should_minus.length == 1);
    TEST_CHECK(should_minus_equal.type == TK_MINUS_EQUAL);
    TEST_CHECK(should_minus_equal.length == 2);
    TEST_CHECK(should_minus_minus.type == TK_MINUS_MINUS);
    TEST_CHECK(should_minus_minus.length == 2);
    TEST_CHECK(should_eof.type == TK_EOF);
    bs_lex_free();
}

void should_identify_single_or_double_character_plus_tokens(void) {
    // given
    const char * source = "+ += ++";
    bs_lex_init(source);

    // when
    bs_token should_plus = next_token();
    bs_token should_plus_equal = next_token();
    bs_token should_plus_plus = next_token();
    bs_token should_eof = next_token();

    // then
    TEST_CHECK(should_plus.type == TK_PLUS);
    TEST_CHECK(should_plus.length == 1);
    TEST_CHECK(should_plus_equal.type == TK_PLUS_EQUAL);
    TEST_CHECK(should_plus_equal.length == 2);
    TEST_CHECK(should_plus_plus.type == TK_PLUS_PLUS);
    TEST_CHECK(should_plus_plus.length == 2);
    TEST_CHECK(should_eof.type == TK_EOF);
    bs_lex_free();
}

void should_identify_single_or_double_character_slash_tokens(void) {
    // given
    const char * source = "/ /=";
    bs_lex_init(source);

    // when
    bs_token should_slash = next_token();
    bs_token should_slash_equal = next_token();
    bs_token should_eof = next_token();

    // then
    TEST_CHECK(should_slash.type == TK_SLASH);
    TEST_CHECK(should_slash.length == 1);
    TEST_CHECK(should_slash_equal.type == TK_SLASH_EQUAL);
    TEST_CHECK(should_slash_equal.length == 2);
    TEST_CHECK(should_eof.type == TK_EOF);
    bs_lex_free();
}

void should_identify_single_or_double_character_star_tokens(void) {
    // given
    const char * source = "* *=";
    bs_lex_init(source);

    // when
    bs_token should_star = next_token();
    bs_token should_star_equal = next_token();
    bs_token should_eof = next_token();

    // then
    TEST_CHECK_(should_star.type == TK_STAR, "%d == %d", should_star.type, TK_STAR);
    TEST_CHECK(should_star.length == 1);
    TEST_CHECK(should_star_equal.type == TK_STAR_EQUAL);
    TEST_CHECK(should_star_equal.length == 2);
    TEST_CHECK(should_eof.type == TK_EOF);
    bs_lex_free();
}

void should_identify_single_or_double_character_and_tokens(void) {
    // given
    const char * source = "& && &=";
    bs_lex_init(source);

    // when
    bs_token should_bit_and = next_token();
    bs_token should_and = next_token();
    bs_token should_bit_and_equal = next_token();
    bs_token should_eof = next_token();

    // then
    TEST_CHECK_(should_bit_and.type == TK_BIT_AND, "Type: %d == %d", should_bit_and.type, TK_BIT_AND);
    TEST_CHECK_(should_bit_and.length == 1, "Length: %d == %d", should_bit_and.length, 1);
    TEST_CHECK_(should_and.type == TK_AND, "Type: %d == %d", should_and.type, TK_AND);
    TEST_CHECK_(should_and.length == 2, "Length: %d == %d", should_and.length, 2);
    TEST_CHECK_(should_bit_and_equal.type == TK_BIT_AND_EQUAL, "Type: %d == %d", should_bit_and_equal.type, TK_BIT_AND_EQUAL);
    TEST_CHECK_(should_bit_and_equal.length == 2, "Length: %d == %d", should_bit_and_equal.length, 2);
    TEST_CHECK(should_eof.type == TK_EOF);
    bs_lex_free();
}

void should_identify_single_or_double_character_or_tokens(void) {
    // given
    const char * source = "| || |=";
    bs_lex_init(source);

    // when
    bs_token should_bit_or = next_token();
    bs_token should_or = next_token();
    bs_token should_bit_or_equal = next_token();
    bs_token should_eof = next_token();

    // then
    TEST_CHECK_(should_bit_or.type == TK_BIT_OR, "Type: %d == %d", should_bit_or.type, TK_BIT_OR);
    TEST_CHECK_(should_bit_or.length == 1, "Length: %d == %d", should_bit_or.length, 1);
    TEST_CHECK_(should_or.type == TK_OR, "Type: %d == %d", should_or.type, TK_OR);
    TEST_CHECK_(should_or.length == 2, "Length: %d == %d", should_or.length, 2);
    TEST_CHECK_(should_bit_or_equal.type == TK_BIT_OR_EQUAL, "Type: %d == %d", should_bit_or_equal.type, TK_BIT_OR_EQUAL);
    TEST_CHECK_(should_bit_or_equal.length == 2, "Length: %d == %d", should_bit_or_equal.length, 2);
    TEST_CHECK(should_eof.type == TK_EOF);
    bs_lex_free();
}


TEST_LIST = {
    {": Should increment line numbers in comments", should_increment_line_number_with_comments},
    {": Should identify '(){}[],.~:;?' as single character tokens", should_identify_single_character_tokens},
    {": Should identify '- -= --' tokens", should_identify_single_or_double_character_minus_tokens},
    {": Should identify '+ += ++' tokens", should_identify_single_or_double_character_plus_tokens},
    {": Should identify '/ /=' tokens", should_identify_single_or_double_character_slash_tokens},
    {": Should identify '* *=' tokens", should_identify_single_or_double_character_star_tokens},
    {": Should identify '& && &=' tokens", should_identify_single_or_double_character_and_tokens},
    {": Should identify '| || |=' tokens", should_identify_single_or_double_character_or_tokens},
    {NULL, NULL}
};