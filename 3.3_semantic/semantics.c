/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab *symtab;
extern Token *currentToken;

Object *lookupObject(char *name)
{
  // TODO
  Scope *scope = symtab->currentScope;
  while (scope != NULL)
  {
    Object *obj;
    while (scope != NULL)
    {
      obj = findObject(scope->objList, name);
      if (obj != NULL)
        return obj;
      scope = scope->outer;
    }
    obj = findObject(symtab->globalObjectList, name);
    if (obj != NULL)
      return obj;
  }
  return NULL;
}

void checkFreshIdent(char *name)
{
  // TODO
  // if (lookupObject(name) != NULL)
  // error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
  if (findObject(symtab->currentScope->objList, name) != NULL)
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);

  //  printf("Check ");
}

Object *checkDeclaredIdent(char *name)
{
  // TODO
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object *checkDeclaredConstant(char *name)
{
  // TODO
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_CONSTANT)
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object *checkDeclaredType(char *name)
{
  // TODO
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_TYPE)
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object *checkDeclaredVariable(char *name)
{
  // TODO
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_VARIABLE)
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

/**
 * Ko can hoan thien
 */
Object *checkDeclaredFunction(char *name)
{
  // TODO
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_FUNCTION)
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object *checkDeclaredProcedure(char *name)
{
  // TODO
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_PROCEDURE)
    error(ERR_INVALID_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object *checkDeclaredLValueIdent(char *name)
{
  // TODO
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind == OBJ_FUNCTION && obj->funcAttrs->scope != symtab->currentScope)
    error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
  return obj;
}
