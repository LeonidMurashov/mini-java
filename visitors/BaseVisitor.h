#pragma once

#include "forward_decl.h"
class BaseVisitor {
public:

  virtual void Visit(Assert *statement) = 0;
  virtual void Visit(Assignment *statement) = 0;
  virtual void Visit(IfStatement *statement) = 0;
  virtual void Visit(Main *statement) = 0;
  virtual void Visit(Print *statement) = 0;
  virtual void Visit(Return *statement) = 0;
  virtual void Visit(StatementsList *list) = 0;
  virtual void Visit(VariableDeclaration *statement) = 0;
  virtual void Visit(WhileLoop *statement) = 0;


  virtual void Visit(AndBinary *statement) = 0;
  virtual void Visit(Constant *number) = 0;
  virtual void Visit(Division *statement) = 0;
  virtual void Visit(Equal *statement) = 0;
  virtual void Visit(Greater *statement) = 0;
  virtual void Visit(Identifier *statement) = 0;
  virtual void Visit(Less *statement) = 0;
  virtual void Visit(Minus *statement) = 0;
  virtual void Visit(Modulo *statement) = 0;
  virtual void Visit(Multiplication *statement) = 0;
  virtual void Visit(NotBinary *statement) = 0;
  virtual void Visit(OrBinary *statement) = 0;
  virtual void Visit(Plus *statement) = 0;

  virtual void Visit(Program *program) = 0;
};
