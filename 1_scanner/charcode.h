/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __CHARCODE_H__
#define __CHARCODE_H__

typedef enum
{
  CHAR_SPACE,       // CHAR: ' '
  CHAR_LETTER,      // CHAR: --word--
  CHAR_DIGIT,       // CHAR: --num--
  CHAR_PLUS,        // CHAR: +
  CHAR_MINUS,       // CHAR: -
  CHAR_TIMES,       // CHAR: *
  CHAR_SLASH,       // CHAR: /
  CHAR_LT,          // CHAR: <
  CHAR_GT,          // CHAR: >
  CHAR_EXCLAMATION, // CHAR: !
  CHAR_EQ,          // CHAR: =
  CHAR_COMMA,       // CHAR: ,
  CHAR_PERIOD,      // CHAR: .
  CHAR_COLON,       // CHAR: :
  CHAR_SEMICOLON,   // CHAR: ;
  CHAR_SINGLEQUOTE, /* CHAR: ' */
  CHAR_LPAR,        // CHAR: (
  CHAR_RPAR,        // CHAR: )
  CHAR_UNKNOWN      // CHAR: ???
} CharCode;

#endif
