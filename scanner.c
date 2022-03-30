/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"

extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/

void skipBlank()
{
  while (currentChar != EOF && charCodes[currentChar] != CHAR_SPACE)
    readChar();
  printf("Current text after Skip blank %c", currentChar);
}

void skipComment()
{
  // (* content *)

  while (1) {
    readChar();

    if(currentChar == EOF) {
      // NOTE: if comment end with EOF -> throw error and exit
      error(ERR_ENDOFCOMMENT, lineNo, colNo);
    } else if (charCodes[currentChar] == CHAR_TIMES) {  // next char is *
      readChar();

      if(currentChar == EOF) {
        error(ERR_ENDOFCOMMENT, lineNo, colNo);
      } else if (charCodes[currentChar] == CHAR_RPAR) {
        readChar();
        return;
      }
    }

  }

  // int mark = 0;
  // while (currentChar != EOF || mark != 2)
  // {
  //   readChar();
  //   if (charCodes[currentChar] == CHAR_TIMES)
  //   {
  //     mark = 1;
  //     printf("mark");
  //   }
  //   else if (
  //       charCodes[currentChar] == CHAR_RPAR && mark == 1)
  //   {
  //     printf("break\n");
  //     readChar();
  //     return;
  //   }
  //   else
  //   {
  //     mark = 0;
  //   }
  // }
  // if (currentChar != EOF)
  //   readChar();
  printf('Skip comment');
}

Token *readIdentKeyword(void)
{
  int ln = lineNo, cn = colNo;
  char kw[1000] = "";
  int i = 0;
  while (charCodes[currentChar] == CHAR_LETTER || charCodes[currentChar] == CHAR_DIGIT)
  {
    // strcat(kw, currentChar);
    // strchr(kw, currentChar);
    kw[i] = currentChar;
    // printf("%s", kw);
    // printf("%c", currentChar);
    readChar();
    i++;
  }
  // readChar();
  printf("[%s] AS [%d]  -End readIdentKeyword\n", kw, checkKeyword(kw));
  TokenType tt = checkKeyword(kw);
  if (tt == TK_NONE)
  {
    tt = TK_IDENT;
  }
  Token *t = makeToken(tt, ln, cn);
  return t;
}

Token *readNumber(void)
{
  int ln = lineNo, cn = colNo;
  int isNumber = 0;
  while (charCodes[currentChar] == CHAR_DIGIT)
  {
    readChar();
  }

  readChar();
  return makeToken(KW_INTEGER, ln, cn);
}

Token *readConstChar(void)
{
  // TODO
}

Token *getToken(void)
{
  Token *token;
  int ln, cn;

  if (currentChar == EOF)
    return makeToken(TK_EOF, lineNo, colNo);

  // printf("--%d--\n", charCodes[currentChar]);
  printf("..%c..\n", currentChar);

  // printf("--getToken \n");

  switch (charCodes[currentChar])
  {
  case CHAR_SPACE:
    skipBlank();
    return getToken();
  case CHAR_LETTER:
    return readIdentKeyword();
  case CHAR_DIGIT:
    return readNumber();
  case CHAR_PLUS:
    token = makeToken(SB_PLUS, lineNo, colNo);
    readChar();
    return token;
    // ....
    // TODO
    // ....
  case CHAR_SEMICOLON:
    readChar();
    return makeToken(SB_SEMICOLON, lineNo, colNo);
  case CHAR_LPAR:
    readChar();
    if (charCodes[currentChar] == CHAR_TIMES)
    {
      printf("Handle Comment\n");
      skipComment();
      printf("Handle Comment END\n");
      return getToken();
    }
  // else
  //   printf("Handle LPar");
  // // if (currentChar != EOF)
  // // readChar();
  // return getToken();
  // case CHAR_UNKNOWN:
  //   printf("%c", currentChar);
  //   return getToken();
  default:
    printf("default: %c\n", currentChar);
    token = makeToken(TK_NONE, lineNo, colNo);
    // printToken(token);
    error(ERR_INVALIDSYMBOL, lineNo, colNo);
    readChar();
    return token;
  }
}

/******************************************************************/

void printToken(Token *token)
{

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType)
  {
  case TK_NONE:
    printf("TK_NONE\n");
    break;
  case TK_IDENT:
    printf("TK_IDENT(%s)\n", token->string);
    break;
  case TK_NUMBER:
    printf("TK_NUMBER(%s)\n", token->string);
    break;
  case TK_CHAR:
    printf("TK_CHAR(\'%s\')\n", token->string);
    break;
  case TK_EOF:
    printf("TK_EOF\n");
    break;

  case KW_PROGRAM:
    printf("KW_PROGRAM\n");
    break;
  case KW_CONST:
    printf("KW_CONST\n");
    break;
  case KW_TYPE:
    printf("KW_TYPE\n");
    break;
  case KW_VAR:
    printf("KW_VAR\n");
    break;
  case KW_INTEGER:
    printf("KW_INTEGER\n");
    break;
  case KW_CHAR:
    printf("KW_CHAR\n");
    break;
  case KW_ARRAY:
    printf("KW_ARRAY\n");
    break;
  case KW_OF:
    printf("KW_OF\n");
    break;
  case KW_FUNCTION:
    printf("KW_FUNCTION\n");
    break;
  case KW_PROCEDURE:
    printf("KW_PROCEDURE\n");
    break;
  case KW_BEGIN:
    printf("KW_BEGIN\n");
    break;
  case KW_END:
    printf("KW_END\n");
    break;
  case KW_CALL:
    printf("KW_CALL\n");
    break;
  case KW_IF:
    printf("KW_IF\n");
    break;
  case KW_THEN:
    printf("KW_THEN\n");
    break;
  case KW_ELSE:
    printf("KW_ELSE\n");
    break;
  case KW_WHILE:
    printf("KW_WHILE\n");
    break;
  case KW_DO:
    printf("KW_DO\n");
    break;
  case KW_FOR:
    printf("KW_FOR\n");
    break;
  case KW_TO:
    printf("KW_TO\n");
    break;

  case SB_SEMICOLON:
    printf("SB_SEMICOLON\n");
    break;
  case SB_COLON:
    printf("SB_COLON\n");
    break;
  case SB_PERIOD:
    printf("SB_PERIOD\n");
    break;
  case SB_COMMA:
    printf("SB_COMMA\n");
    break;
  case SB_ASSIGN:
    printf("SB_ASSIGN\n");
    break;
  case SB_EQ:
    printf("SB_EQ\n");
    break;
  case SB_NEQ:
    printf("SB_NEQ\n");
    break;
  case SB_LT:
    printf("SB_LT\n");
    break;
  case SB_LE:
    printf("SB_LE\n");
    break;
  case SB_GT:
    printf("SB_GT\n");
    break;
  case SB_GE:
    printf("SB_GE\n");
    break;
  case SB_PLUS:
    printf("SB_PLUS\n");
    break;
  case SB_MINUS:
    printf("SB_MINUS\n");
    break;
  case SB_TIMES:
    printf("SB_TIMES\n");
    break;
  case SB_SLASH:
    printf("SB_SLASH\n");
    break;
  case SB_LPAR:
    printf("SB_LPAR\n");
    break;
  case SB_RPAR:
    printf("SB_RPAR\n");
    break;
  case SB_LSEL:
    printf("SB_LSEL\n");
    break;
  case SB_RSEL:
    printf("SB_RSEL\n");
    break;
  }
}

int scan(char *fileName)
{
  Token *token;

  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  token = getToken();
  printToken(token);
  printf(":%d:", token->tokenType);
  // token = getToken();
  // printToken(token);
  // printf(":%d:", token->tokenType);

  while (token->tokenType != TK_EOF)
  {
    // i++;
    // printf("While not end");
    printToken(token);
    free(token);
    token = getToken();
    // if (i > 5)
    //   break;
  }

  // free(token);
  // closeInputStream();
  // return IO_SUCCESS;
}

/******************************************************************/

main(int argc, char *argv[])
{
  printf("STARt\n");
  // openInputStream(argv[1]);
  if (argc > 1)
  {
    printf("%d", scan(argv[1]));
  }
  else
  {
    printf("Can truyen tham so");
  }

  // return -1;
  //  getch();
}

// return 0;
