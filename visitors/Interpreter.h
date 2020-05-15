#pragma once

#include "BaseVisitor.h"
#include "forward_decl.h"
#include <map>

class Interpreter : public BaseVisitor {
public:
  void Visit(Assert *statement) override;
  void Visit(Assignment *statement) override;
  void Visit(IfStatement *statement) override;
  void Visit(Main *statement) override;
  void Visit(Print *statement) override;
  void Visit(Return *statement) override;
  void Visit(StatementsList *list) override;
  void Visit(VariableDeclaration *statement) override;
  void Visit(WhileLoop *statement) override;
  void Visit(AndBinary *statement) override;
  void Visit(Constant *number) override;
  void Visit(Division *statement) override;
  void Visit(Equal *statement) override;
  void Visit(Greater *statement) override;
  void Visit(Identifier *statement) override;
  void Visit(Less *statement) override;
  void Visit(Minus *statement) override;
  void Visit(Modulo *statement) override;
  void Visit(Multiplication *statement) override;
  void Visit(NotBinary *statement) override;
  void Visit(OrBinary *statement) override;
  void Visit(Plus *statement) override;
  int Visit(Program *program) override;

private:
  int tos_value = 0;
  std::map<std::string, int> global_scope_;
};
