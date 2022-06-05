/*
Thay the cac luat tu vung trong project1 bang cac luat sau:
Luat cho dinh danh:
Dinh danh bao gom chu cai (hoa, thuong), chu so va dau gach duoi(_)
1.Ky tu dau la chu cai
2.Dinh danh khong duoc trung voi tu khoa.
3. Do dai dinh danh khong vuot qua 15
4.Dinh danh co phan biet chu hoa/chu thuong
Luat cho tu khoa:
Tu khoa khong phan biet chu hoa chu thuong
Luat cho chu thich:
*/
// Bo chu thich giua (* va  *).Chu thich tren nhieu dong :  Giua /* va */
// Luat cho cac ky hieu dac biet:
// Toan tu khac ><
// Luat cho hang ky tu?xau ky tu:
// Hang xau ky tu duoc phep trong KPL.
//      Mot hang xau ky tu co the chua mot chuoi cac ky tu in duoc,
//      do dai khong qua 255, duoc dat trong cap dau nhay don.
//      Neu dau nhay don duoc viet trong hang xau ky tu, phai viet 2 lan.

/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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
    while (currentChar != EOF && charCodes[currentChar] == CHAR_SPACE)
        readChar();
    // printf("SKIP BLANK %c", currentChar);
}

//  /* comment */
void skipComment()
{
    while (1)
    {
        readChar();

        // if end of file -> error
        // if next char is */ -> break
        if (currentChar == EOF)
        {
            error(ERR_ENDOFCOMMENT, lineNo, colNo);
        }
        else if (charCodes[currentChar] == CHAR_TIMES)
        {
            readChar();

            if (currentChar == EOF)
            {
                error(ERR_ENDOFCOMMENT, lineNo, colNo);
            }
            else if (charCodes[currentChar] == CHAR_SLASH)
            {
                readChar();
                return;
            }
        }
    }
    // printf('Skip comment');
}
/**
 * @brief Định danh / từ khóa:
 *
 * - Bất đầu: chữ ( đã check trong getToken )
 * - Độ dài: <= 15 -> chi lay 15 ky tu
 * - Phân biệt hoa / thường:
 *    + Từ khóa: k ( checkKeyword k phân biệt hoa / thường )
 *    + Định danh: có
 * - NEW: Bao gom dau gach duoi
 *
 * @return Token*
 */
Token *readIdentKeyword(void)
{
    int ln = lineNo, cn = colNo;
    char kw[MAX_IDENT_LEN] = "";
    int i = 0;
    while (
        charCodes[currentChar] == CHAR_LETTER ||
        charCodes[currentChar] == CHAR_DIGIT ||
        currentChar == '_')
    {
        if (i < MAX_IDENT_LEN)
        {
            kw[i] = currentChar;
            readChar();
            i++;
            // break;
            // error(ERR_IDENTTOOLONG, ln, cn);
        }
        else
        {
            readChar();
            // printf("%c", currentChar);
        }
    }
    kw[i] = '\0';
    // printf("[%s] AS [%d]  -End readIdentKeyword\n", kw, checkKeyword(kw));
    TokenType tt = checkKeyword(kw);
    // printf("%s, %d\n", kw, tt);
    // NOTE: check if TK_NONE -> TK_INDENT
    if (tt == TK_NONE)
    {
        tt = TK_IDENT;
    }
    Token *t = makeToken(tt, ln, cn);
    strcpy(t->string, kw);
    return t;
}

/**
 * @brief: Số:
 * - Nguyên k âm
 * - lỗi: Number too long khi > INT_MAX
 *
 * @return Token*
 */
Token *readNumber(void)
{
    int count = 0;
    Token *token = makeToken(TK_NUMBER, lineNo, colNo);

    while (charCodes[currentChar] == CHAR_DIGIT)
    {
        if (count > 10)
        {
            error(ERR_NUMBERTOOLONG, token->lineNo, token->colNo);
        }
        token->string[count] = currentChar;
        readChar();
        count++;
    }

    // END OF NUMBER
    token->string[count] = '\0';
    token->value = atoi(token->string);

    // printf("INT_MAX: %d\n", INT_MAX);
    // printf("ITEM:    %ld\n", atol(token->string));
    // printf("ITEM_STR:%s\n", token->string);

    // HANDLE NUMBER > INT_MAX
    if (count == 10 && atol(token->string) > INT_MAX)
    {
        error(ERR_NUMBERTOOLONG, token->lineNo, token->colNo);
    }

    return token;
}

/**
 * @brief Hằng ký tự
 *
 * - Bất đầu: ký tự '
 * - Kết thúc: ký tự '
 * - NOTE: ký tự '' = '
 * - NOTE: Chưa check string length
 *
 * @return Token*
 */
Token *readConstChar(void)
{
    Token *token = makeToken(TK_CHAR, lineNo, colNo);
    // NOTE: currentChar = '\'';
    int count = 0;

    while (1)
    {
        readChar();
        // printf("current char: %d %d\n", currentChar == '\'', '\'');
        // NEW: handle ''
        if (charCodes[currentChar] == CHAR_SINGLEQUOTE)
        {
            readChar();
            if (currentChar == EOF)
            {
                error(ERR_INVALIDCHARCONSTANT, lineNo, colNo);
            }
            else if (count > 256)
            {
                // FIXME: Khong co ERR_CHARCONSTANTTOOLONG
                error(ERR_INVALIDCHARCONSTANT, lineNo, colNo);
            }
            else if (charCodes[currentChar] == CHAR_SINGLEQUOTE)
            {
                token->string[count] = currentChar;
                count++;
                // NEW: Check string length
            }
            else
            {
                // '... -> end comment
                break;
            }
        }
        // handle end of char
        else if (currentChar == EOF)
        {
            error(ERR_INVALIDCHARCONSTANT, lineNo, colNo);
        }
        else
        {
            token->string[count] = currentChar;
            count++;
        }
    }

    token->string[count] = '\0';
    return token;
}

Token *getToken(void)
{
    Token *token;
    int ln = lineNo, cn = colNo;

    if (currentChar == EOF)
        return makeToken(TK_EOF, lineNo, colNo);
    // printf("..%c..\n", currentChar);

    switch (charCodes[currentChar])
    {
    case CHAR_SPACE:
        skipBlank();
        return getToken();
    case CHAR_LETTER:
        return readIdentKeyword();
    case CHAR_DIGIT:
        return readNumber();
    // operator
    case CHAR_PLUS:
        token = makeToken(SB_PLUS, lineNo, colNo);
        readChar();
        return token;
    case CHAR_MINUS:
        token = makeToken(SB_MINUS, lineNo, colNo);
        readChar();
        return token;
    case CHAR_TIMES:
        token = makeToken(SB_TIMES, lineNo, colNo);
        readChar();
        return token;
    /**
     * CURRENT_CHAR: /
     * - NEXT_CHAR: * -> NEW: COMMENT
     * - OTHER -> /
     */
    case CHAR_SLASH:
        token = makeToken(SB_SLASH, lineNo, colNo);
        readChar();
        switch (charCodes[currentChar])
        {
        case CHAR_TIMES:
            free(token);
            skipComment();
            return getToken();
        default:
            return token;
        }
    case CHAR_EQ:
        token = makeToken(SB_EQ, lineNo, colNo);
        readChar();
        return token;
    case CHAR_COMMA:
        // Token Comma
        token = makeToken(SB_COMMA, lineNo, colNo);
        readChar();
        return token;
    case CHAR_SEMICOLON:
        token = makeToken(SB_SEMICOLON, lineNo, colNo);
        readChar();
        return token;
    case CHAR_RPAR:
        token = makeToken(SB_RPAR, lineNo, colNo);
        readChar();
        return token;
    /**
     * CURRENT_CHAR: (
     * - NEXT_CHAR: .
     * - ELSE
     */
    case CHAR_LPAR:
        token = makeToken(TK_NONE, lineNo, colNo);
        readChar();
        switch (charCodes[currentChar])
        {
        case CHAR_PERIOD:
            token->tokenType = SB_LSEL;
            readChar();
            return token;
        // case CHAR_SPACE:
        //     readChar();
        //     return getToken();
        default:
            token->tokenType = SB_LPAR;
            return token;
        }

    /**
     * CURRENT_CHAR: >
     * - NEXT_CHAR: =
     * - NEXT_CHAR: < -> NEW: SB_NEQ
     * - ELSE
     */
    case CHAR_GT:
        token = makeToken(SB_GT, lineNo, colNo);
        // If next character is '='
        readChar();
        if (charCodes[currentChar] == CHAR_EQ)
        {
            // Token is Greater Than
            token->tokenType = SB_GE;
            readChar();
        }
        else if (charCodes[currentChar] == CHAR_LT)
        {
            // Token is Not Equal
            token->tokenType = SB_NEQ;
            readChar();
        }
        return token;
    /**
     * CURRENT_CHAR: <
     * - NEXT_CHAR: =
     * - ELSE
     */
    case CHAR_LT:
        // Empty token
        token = makeToken(TK_NONE, lineNo, colNo);

        // Check next character
        readChar();
        switch (charCodes[currentChar])
        {
        case CHAR_EQ:
            // Token Lest Than or Equal
            token->tokenType = SB_LE;
            readChar();
            return token;
        default:
            // Token Lest Than
            token->tokenType = SB_LT;
            return token;
        }
        /**
         * NOTE: Deprecated
         * CURRENT_CHAR: !
         * - NEXT_CHAR: =
         * - ELSE throw error
         */
        // case CHAR_EXCLAMATION:
        //     // Make empty token
        //     token = makeToken(TK_NONE, lineNo, colNo);

        //     // If next character is not '='
        //     readChar();
        //     if (charCodes[currentChar] != CHAR_EQ)
        //     {
        //         // it is an invalid token
        //         error(ERR_INVALIDSYMBOL, token->lineNo, token->colNo);
        //     }
        //     else
        //     {
        //         token->tokenType = SB_NEQ;
        //     }
        //     return token;

    case CHAR_PERIOD:
        // Token Period
        token = makeToken(SB_PERIOD, lineNo, colNo);

        // If next character is Right Parenthesis
        readChar();
        if (charCodes[currentChar] == CHAR_RPAR)
        {
            // it is token Right Parenthesis
            token->tokenType = SB_RSEL;
            readChar();
        }
        return token;
    case CHAR_COLON:
        // Token Semicolon
        token = makeToken(SB_SEMICOLON, lineNo, colNo);

        // If next character is Equal
        readChar();
        if (charCodes[currentChar] == CHAR_EQ)
        {
            // it is token Assignment
            token->tokenType = SB_ASSIGN;
            readChar();
        }
        return token;
    case CHAR_SINGLEQUOTE:
        return readConstChar();
        // NOTE
    default:
        // printf("default: %c\n", currentChar);
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
    // NOTE: HANDLE TOKEN
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

    while (token->tokenType != TK_EOF)
    {
        printToken(token);
        free(token);
        token = getToken();
    }

    free(token);
    closeInputStream();
    return IO_SUCCESS;
}

/**
 * ================================================================
 */

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("%d", scan(argv[1]));
    }
    else
    {
        printf("scanner: no input file.\n");
    }

    return 0;
}
