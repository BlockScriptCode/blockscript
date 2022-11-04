#include <stdio.h>
#include "bs_ast.h"

AST * ast_new(AST ast) {
  AST * ptr = malloc(sizeof(AST));
  if (ptr) *ptr = ast;
  return ptr;
}  

void ast_free(AST *ptr) {
  // AST ast = *ptr;
  // switch (ast.tag) {
  //   case AST_NUMBER: {
  //     struct AST_NUMBER data = ast.data.AST_NUMBER;
  //     break;
  //   }
  //   case AST_ADD: {
  //     struct AST_ADD data = ast.data.AST_ADD;
  //     ast_free(data.left);
  //     ast_free(data.right);
  //     break;
  //   }
  //   case AST_MUL: {
  //     struct AST_MUL data = ast.data.AST_MUL;
  //     ast_free(data.left);
  //     ast_free(data.right);
  //     break;
  //   }
  // } 
  // free(ptr);
} 

static char * operator_str(ast_operator operator) {
  switch (operator)
  {
  case BIT_NOT: return "\"~\"";
  case BANG: return "\"!\"";
  case MINUS: return "\"-\"";
  case MINUS_MINUS: return "\"--\"";
  case PLUS: return "\"+\"";
  case PLUS_PLUS: return "\"++\"";
  case SLASH: return "\"/\"";
  case STAR: return "\"*\"";
  case BIT_AND: return "\"&\"";
  case BIT_OR: return "\"|\"";
  case EQUAL_EQUAL: return "\"==\"";
  case GREATER: return "\">\"";
  case BIT_SHIFT_RIGHT: return "\">>\"";
  case GREATER_EQUAL: return "\">=\"";
  case LESS: return "\"<\"";
  case BIT_SHIFT_LEFT: return "\"<<\"";
  case LESS_EQUAL: return "\"<=\"";
  default:
    return "Operator Invalid";
  }
  
}

static void print_tabs(int depth) {
    for(int i = 0;i<depth;i++) 
      printf("    ");
}

static void print_type(ast_type type, int depth) {
  printf("{\n");
  print_tabs(depth);
  printf("\"type\": ");
  switch (type) {
    case INTEGER_LITERAL:
      printf("\"literal\",\n");
      break;
    case UNARY_EXPRESSION:
      printf("\"unary-expression\",\n");
      break;
    case BINARY_EXPRESSION:
      printf("\"binary-expression\",\n");
      break;
    case CONDITIONAL_EXPRESSION:
      printf("\"conditional-expression\",\n");
      break;
    case EXPRESSION_STATEMENT:
      printf("\"expression-statement\",\n");
      break;
    default:
      break;
  }

}

static void ast_print_depth(AST * ast, int depth, bool is_last) {
  ast_type current_type = ast->type;
  print_type(current_type, depth+1);
  print_tabs(depth+1);
  switch (current_type) {
    case INTEGER_LITERAL:
      printf("\"data-type\": \"int\",\n");
      print_tabs(depth+1);
      printf("\"value\": %d\n",AST_DATA(ast, INTEGER_LITERAL).number);
      break;
    case UNARY_EXPRESSION:
      printf("\"operator\": %s,\n", operator_str(AST_DATA(ast, UNARY_EXPRESSION).operator));
      print_tabs(depth+1);
      printf("\"argument\": ");
      ast_print_depth(AST_DATA(ast, UNARY_EXPRESSION).argument, depth + 1, true);
      
      break;
    case BINARY_EXPRESSION:
      printf("\"operator\": %s,\n", operator_str(AST_DATA(ast, BINARY_EXPRESSION).operator));
      print_tabs(depth+1);
      printf("\"left\": ");
      ast_print_depth(AST_DATA(ast, BINARY_EXPRESSION).left, depth + 1, false);
      print_tabs(depth+1);
      printf("\"right\": ");
      ast_print_depth(AST_DATA(ast, BINARY_EXPRESSION).right, depth + 1, true);
      break;
    case CONDITIONAL_EXPRESSION:
      
      break;
    case EXPRESSION_STATEMENT:
      
      break;
  }
  print_tabs(depth);
  printf("}%c\n", is_last ? ' ': ',');
}

void ast_print(AST * ast) {
  ast_type current_type = ast->type;
  print_type(current_type, 1);
  print_tabs(1);
  switch (current_type) {
    case INTEGER_LITERAL:
      printf("\"data-type\": \"int\",\n");
      print_tabs(1);
      printf("\"value\": %d\n",AST_DATA(ast, INTEGER_LITERAL).number);
      break;
    case UNARY_EXPRESSION:
      printf("\"operator\": %s,\n", operator_str(AST_DATA(ast, UNARY_EXPRESSION).operator));
      print_tabs(1);
      printf("\"argument\": ");
      ast_print_depth(AST_DATA(ast, UNARY_EXPRESSION).argument, 1, true);
      
      break;
    case BINARY_EXPRESSION:
      printf("\"operator\": %s,\n", operator_str(AST_DATA(ast, BINARY_EXPRESSION).operator));
      print_tabs(1);
      printf("\"left\": ");
      ast_print_depth(AST_DATA(ast, BINARY_EXPRESSION).left, 1, false);
      print_tabs(1);
      printf("\"right\": ");
      ast_print_depth(AST_DATA(ast, BINARY_EXPRESSION).right, 1, true);
      break;
    case CONDITIONAL_EXPRESSION:
      
      break;
    case EXPRESSION_STATEMENT:
      
      break;
  }
  printf("}\n");
}