/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#define MAX_IDENT_LEN 15
#define KEYWORDS_COUNT 20

typedef enum
{
  TK_NONE,   // Đại diện cho một lỗi
  TK_IDENT,  // Định danh
  TK_NUMBER, // Số
  TK_CHAR,   // Hằng ký tự
  TK_EOF,    // Kết thúc chương trình

  KW_PROGRAM,
  KW_CONST,
  KW_TYPE,
  KW_VAR,
  KW_INTEGER,
  KW_CHAR,
  KW_ARRAY,
  KW_OF,
  KW_FUNCTION,
  KW_PROCEDURE,
  KW_BEGIN,
  KW_END,
  KW_CALL,
  KW_IF,
  KW_THEN,
  KW_ELSE,
  KW_WHILE,
  KW_DO,
  KW_FOR,
  KW_TO,

  SB_SEMICOLON, // SB: ;
  SB_COLON,     // SB: :
  SB_PERIOD,    // SB: .
  SB_COMMA,     // SB: ,
  SB_ASSIGN,    // SB: :=
  SB_EQ,        // SB: =
  SB_NEQ,       // SB: !=
  SB_LT,        // SB: <
  SB_LE,        // SB: <=
  SB_GT,        // SB: >
  SB_GE,        // SB: >=
  SB_PLUS,      // SB: +
  SB_MINUS,     // SB: -
  SB_TIMES,     // SB: *
  SB_SLASH,     // SB: /
  SB_LPAR,      // SB: (
  SB_RPAR,      // SB: )
  SB_LSEL,      // SB: (.
  SB_RSEL       // SB: .)
} TokenType;

typedef struct
{
  char string[MAX_IDENT_LEN + 1];
  int lineNo, colNo;
  TokenType tokenType;
  int value;
} Token;

TokenType checkKeyword(char *string);
Token *makeToken(TokenType tokenType, int lineNo, int colNo);

#endif
