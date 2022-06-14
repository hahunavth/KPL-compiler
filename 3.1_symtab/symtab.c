/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object *obj);
void freeScope(Scope *scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab *symtab;
Type *intType;
Type *charType;

/******************* Type utilities ******************************/

Type *makeIntType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type *makeCharType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type *makeArrayType(int arraySize, Type *elementType)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type *duplicateType(Type *type)
{
  // TODO
  Type *dType = (Type *)malloc(sizeof(Type));
  dType->typeClass = type->typeClass;
  dType->arraySize = type->arraySize;
  if (type->elementType->typeClass != TP_ARRAY)
  {
    dType->elementType = duplicateType(type->elementType);
    dType->arraySize = type->arraySize;
  }
  return dType;
}

int compareType(Type *type1, Type *type2)
{
  // TODO
  if (type1->typeClass != type2->typeClass)
  {
    return 0;
  }
  else if (type1->typeClass == TP_INT)
  {
    return 1;
  }
  else if (type1->typeClass == TP_CHAR)
  {
    return 1;
  }
  else if (type1->typeClass == TP_ARRAY)
  {
    if (type1->arraySize != type2->arraySize)
    {
      return 0;
    }
    else
    {
      return compareType(type1->elementType, type2->elementType);
    }
  }
  else
  {
    return 0;
  }
}

void freeType(Type *type)
{
  // TODO
  if (type->typeClass == TP_ARRAY)
  {
    freeType(type->elementType);
    free(type);
  }
  else if (type->typeClass == TP_INT || type->typeClass == TP_CHAR)
  {
    free(type);
  }
}

/******************* Constant utility ******************************/

ConstantValue *makeIntConstant(int i)
{
  // TODO
  ConstantValue *cv = (ConstantValue *)malloc(sizeof(ConstantValue));
  cv->intValue = i;
  cv->type = TP_INT;

  return cv;
}

ConstantValue *makeCharConstant(char ch)
{
  // TODO
  ConstantValue *cv = (ConstantValue *)malloc(sizeof(ConstantValue));
  cv->charValue = ch;
  cv->type = TP_CHAR;

  return cv;
}

ConstantValue *duplicateConstantValue(ConstantValue *v)
{
  // TODO
  ConstantValue *cv = (ConstantValue *)malloc(sizeof(ConstantValue));
  cv->type = v->type;
  if (v->type == TP_INT)
  {
    cv->intValue = v->intValue;
  }
  else if (v->type == TP_CHAR)
  {
    cv->charValue = v->charValue;
  }

  return cv;
}

/******************* Object utilities ******************************/

Scope *createScope(Object *owner, Scope *outer)
{
  Scope *scope = (Scope *)malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object *createProgramObject(char *programName)
{
  Object *program = (Object *)malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes *)malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program, NULL);
  symtab->program = program;

  return program;
}

Object *createConstantObject(char *name)
{
  // TODO
  Object *constant = (Object *)malloc(sizeof(Object));
  strcpy(constant->name, name);
  constant->kind = OBJ_CONSTANT;
  constant->constAttrs = (ConstantAttributes *)malloc(sizeof(ConstantAttributes));

  return constant;
}

Object *createTypeObject(char *name)
{
  // TODO
  Object *typeObj = (Object *)malloc(sizeof(Object));
  strcpy(typeObj->name, name);
  typeObj->typeAttrs = (TypeAttributes *)malloc(sizeof(TypeAttributes));
  typeObj->kind = OBJ_TYPE;

  return typeObj;
}

Object *createVariableObject(char *name)
{
  // TODO
  Object *obj = (Object *)malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->varAttrs = (VariableAttributes *)malloc(sizeof(VariableAttributes));
  obj->kind = OBJ_VARIABLE;
  obj->varAttrs->scope = symtab->currentScope;

  return obj;
}

Object *createFunctionObject(char *name)
{
  // TODO
  Object *func = (Object *)malloc(sizeof(Object));
  strcpy(func->name, name);
  func->kind = OBJ_FUNCTION;
  func->funcAttrs = (FunctionAttributes *)malloc(sizeof(FunctionAttributes));
  func->funcAttrs->paramList = NULL;
  func->funcAttrs->scope = createScope(func, symtab->currentScope);

  return func;
}

Object *createProcedureObject(char *name)
{
  // TODO
  Object *proc = (Object *)malloc(sizeof(Object));
  strcpy(proc->name, name);
  proc->kind = OBJ_PROCEDURE;
  proc->procAttrs = (ProcedureAttributes *)malloc(sizeof(ProcedureAttributes));
  proc->procAttrs->paramList = (ObjectNode *)malloc(sizeof(ObjectNode));
  proc->procAttrs->scope = createScope(proc, symtab->currentScope);

  return proc;
}

Object *createParameterObject(char *name, enum ParamKind kind, Object *owner)
{
  // TODO
  Object *parameter = (Object *)malloc(sizeof(Object));
  strcpy(parameter->name, name);
  parameter->kind = OBJ_PARAMETER;
  parameter->paramAttrs = (ParameterAttributes *)malloc(sizeof(ParameterAttributes));
  parameter->paramAttrs->kind = kind;
  parameter->paramAttrs->function = owner;

  return parameter;
}

void freeObject(Object *obj)
{
  // TODO
  free(obj->name);
  switch (obj->kind)
  {
  case OBJ_CONSTANT:
    free(obj->constAttrs->value);
    free(obj->constAttrs);
    break;
  case OBJ_TYPE:
    freeType(obj->typeAttrs->actualType);
    free(obj->typeAttrs);
    break;
  case OBJ_VARIABLE:
    free(obj->varAttrs);
    break;
  case OBJ_PROGRAM:
    freeScope(obj->progAttrs->scope);
    free(obj->progAttrs);
    break;
  case OBJ_PARAMETER:
    freeType(obj->paramAttrs->type);
    free(obj->paramAttrs);
    break;
  case OBJ_FUNCTION:
    freeReferenceList(obj->funcAttrs->paramList);
    freeType(obj->funcAttrs->returnType);
    freeScope(obj->funcAttrs->scope);
    free(obj->funcAttrs);
    break;
  case OBJ_PROCEDURE:
    freeReferenceList(obj->procAttrs->paramList);
    freeScope(obj->procAttrs->scope);
    free(obj->funcAttrs);
    break;
  }
}

void freeScope(Scope *scope)
{
  // TODO
  freeObjectList(scope->objList);
  free(scope);
}

void freeObjectList(ObjectNode *objList)
{
  // TODO
  if (objList != NULL)
  {
    freeObjectList(objList->next);
    freeObject(objList->object);
    free(objList);
  }
}

void freeReferenceList(ObjectNode *objList)
{
  // TODO
  if (objList != NULL)
  {
    freeReferenceList(objList->next);
    free(objList);
  }
}

void addObject(ObjectNode **objList, Object *obj)
{
  ObjectNode *node = (ObjectNode *)malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL)
    *objList = node;
  else
  {
    ObjectNode *n = *objList;
    while (n->next != NULL)
      n = n->next;
    n->next = node;
  }
}

Object *findObject(ObjectNode *objList, char *name)
{
  // TODO
  while (objList != NULL)
  {
    if (strcmp(objList->object->name, name) == 0)
      return objList->object;
    objList = objList->next;
  }

  return NULL;
}

/******************* others ******************************/

void initSymTab(void)
{
  Object *obj;
  Object *param;

  symtab = (SymTab *)malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;

  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void)
{
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope *scope)
{
  // printf("entering block %s\n", scope->owner->name);
  // if (symtab->currentScope != NULL)
  // {
  //   printf("from: %s\n", symtab->currentScope->owner->name);
  // }
  symtab->currentScope = scope;
}

void exitBlock(void)
{
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object *obj)
{
  if (obj->kind == OBJ_PARAMETER)
  {
    Object *owner = symtab->currentScope->owner;
    switch (owner->kind)
    {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }

  addObject(&(symtab->currentScope->objList), obj);

  // printf("Declare: %s in %s\n", obj->name, symtab->currentScope->owner->name);
}
