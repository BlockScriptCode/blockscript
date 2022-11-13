#include <stdio.h>
#include "bs_ast.h"

AST * ast_new(AST ast) {
  AST * ptr = malloc(sizeof(AST));
  if (ptr) *ptr = ast;
  return ptr;
}  

void ast_free(AST *ptr) {
  AST ast = *ptr;
  switch (ast.type) {
    case LITERAL: {
      free_value(ast.data.LITERAL.value);
      break;
    }
    case UNARY_EXPRESSION: {
      struct UNARY_EXPRESSION data = ast.data.UNARY_EXPRESSION;
      ast_free(data.argument);
      break;
    }
    case BINARY_EXPRESSION: {
      struct BINARY_EXPRESSION data = ast.data.BINARY_EXPRESSION;
      ast_free(data.left);
      ast_free(data.right);
      break;
    }
    case CONDITIONAL_EXPRESSION: {
      struct CONDITIONAL_EXPRESSION data = ast.data.CONDITIONAL_EXPRESSION;
      ast_free(data.test);
      ast_free(data.consequent);
      ast_free(data.alternate);
      break;
    }
    case EXPRESSION_STATEMENT: {
      struct EXPRESSION_STATEMENT data = ast.data.EXPRESSION_STATEMENT;
      ast_free(data.expression);
      break;
    }
  } 
  free(ptr);
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
    case LITERAL:
      printf("\"literal\",\n");
      break;
    case IDENTIFIER:
      printf("\"identifier\",\n");
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
    case VARIABLE_DECLARATION:
      printf("\"variable-declaration\",\n");
      break;
    case VARIABLE_DECLARATOR:
      printf("\"variable-declarator\",\n");
      break;
    default:
      break;
  }

}

static void print_literal(bs_value * literal_value, int depth) {
    bs_value value = *literal_value;
    switch (value.type)
    {
    case BS_BOOL:
      printf("\"data-type\": \"bool\",\n");
      print_tabs(depth);
      printf("\"value\": %d,\n", AS_BOOL_CVAL(value));
      print_tabs(depth);
      char * bool_value = AS_BOOL_CVAL(value) == 0 ? "false" : "true";
      printf("\"raw\": \"%s\"\n", bool_value);
      break;
    case BS_INT8:
      printf("\"data-type\": \"int8\",\n");
      print_tabs(depth);
      printf("\"value\": %d,\n", AS_INT8_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%d\"\n", AS_INT8_CVAL(value));
      break;
    case BS_UINT8:
      printf("\"data-type\": \"u_int8\",\n");
      print_tabs(depth);
      printf("\"value\": %d,\n", AS_UINT8_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%d\"\n", AS_UINT8_CVAL(value));
      break;
    case BS_INT16:
      printf("\"data-type\": \"int16\",\n");
      print_tabs(depth);
      printf("\"value\": %d,\n", AS_INT16_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%d\"\n", AS_INT16_CVAL(value));
      break;
    case BS_UINT16:
      printf("\"data-type\": \"u_int16\",\n");
      print_tabs(depth);
      printf("\"value\": %d,\n", AS_UINT16_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%d\"\n", AS_UINT16_CVAL(value));
      break;
    case BS_INT32:
      printf("\"data-type\": \"int32\",\n");
      print_tabs(depth);
      printf("\"value\": %d,\n", AS_INT32_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%d\"\n", AS_INT32_CVAL(value));
      break;
    case BS_UINT32:
      printf("\"data-type\": \"u_int32\",\n");
      print_tabs(depth);
      printf("\"value\": %d,\n", AS_UINT32_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%d\"\n", AS_UINT32_CVAL(value));
      break;
    case BS_INT64:
      printf("\"data-type\": \"int64\",\n");
      print_tabs(depth);
      printf("\"value\": %ld,\n", AS_INT64_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%ld\"\n", AS_INT64_CVAL(value));
      break;
    case BS_UINT64:
      printf("\"data-type\": \"u_int64\",\n");
      print_tabs(depth);
      printf("\"value\": %ld,\n", AS_UINT64_CVAL(value));
      print_tabs(depth);
      printf("\"raw\": \"%ld\"\n", AS_UINT64_CVAL(value));
      break;
    default:
      break;
    }
    
}

static char * get_type_str(ast_variable_type type) {
  switch (type)
  {
    case INT8: return "int8";
    case UINT8: return "u_int8";
    case INT16: return "int16";
    case UINT16: return "u_int16";
    case INT32: return "int32";
    case UINT32: return "u_int32";
    case INT64: return "int64";
    case UINT64: return "u_int64";
  }
  return "unknown";
}

static void ast_print_depth(AST * ast, int depth, bool is_last) {
  ast_type current_type = ast->type;
  print_type(current_type, depth+1);
  print_tabs(depth+1);
  switch (current_type) {
    case LITERAL:
      print_literal(AST_DATA(ast, LITERAL).value, depth + 1);
      break;
    case IDENTIFIER:
      printf("\"name\": \"%.*s\",\n", AST_DATA(ast, IDENTIFIER).length, AST_DATA(ast, IDENTIFIER).name);
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
    case VARIABLE_DECLARATION:
      printf("\"kind:\" \"%s\",", AST_DATA(ast, VARIABLE_DECLARATION).kind == VAL ? "val": "var");
      print_tabs(depth+1);
      printf("\"type:\" \"%s\",", get_type_str(AST_DATA(ast, VARIABLE_DECLARATION).type));
      print_tabs(depth+1);
      printf("\"declaration\": ");
      ast_print_depth(AST_DATA(ast, VARIABLE_DECLARATION).declaration, depth + 1, true);
      break;
    case VARIABLE_DECLARATOR:
      printf("\"id:\" ");
      ast_print_depth(AST_DATA(ast, VARIABLE_DECLARATOR).id, depth + 1, false);
      print_tabs(depth+1);
      printf("\"init\": ");
      ast_print_depth(AST_DATA(ast, VARIABLE_DECLARATOR).init, depth + 1, true);
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
    case LITERAL:
      print_literal(AST_DATA(ast, LITERAL).value, 1);
      break;
    case IDENTIFIER:
      printf("\"name\": \"%.*s\",\n", AST_DATA(ast, IDENTIFIER).length, AST_DATA(ast, IDENTIFIER).name);
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
    case VARIABLE_DECLARATION:
      printf("\"kind:\" \"%s\",\n", AST_DATA(ast, VARIABLE_DECLARATION).kind == VAL ? "val": "var");
      print_tabs(1);
      printf("\"type:\" \"%s\",\n", get_type_str(AST_DATA(ast, VARIABLE_DECLARATION).type));
      print_tabs(1);
      printf("\"declaration\": ");
      ast_print_depth(AST_DATA(ast, VARIABLE_DECLARATION).declaration, 1, true);
      break;
    case VARIABLE_DECLARATOR:
      printf("\"id:\" ");
      ast_print_depth(AST_DATA(ast, VARIABLE_DECLARATOR).id, 1, false);
      print_tabs(1);
      printf("\"init\": ");
      ast_print_depth(AST_DATA(ast, VARIABLE_DECLARATOR).init, 1, true);
      break;
  }
  printf("}\n");
}