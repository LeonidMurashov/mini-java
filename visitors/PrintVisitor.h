#pragma once
#include "BaseVisitor.h"
#include "forward_decl.h"
#include <expressions/BaseExpression.h>
#include <fstream>
#include <string>
class PrintVisitor : public BaseVisitor {
public:
  explicit PrintVisitor(const std::string &path)
      : fout(path, std::ios_base::out) {}
  ~PrintVisitor() { fout.close(); }

  int Visit(Program *program) override;
  void Visit(Main *statement) override;
  void Visit(StatementsList *list) override;
  void Visit(Constant *number) override;
  void Visit(Print *statement) override;

  template <class T> void VisitTerminal(T terminal);
  void VisitUnary(const std::string &name, ASTNode *arg);
  void VisitBinary(const std::string &name, ASTNode *left, ASTNode *right);
  void VisitTernary(const std::string &name, ASTNode *first, ASTNode *second,
                    ASTNode *third);

  void Visit(Plus *statement) override;
  void Visit(Minus *statement) override;
  void Visit(Multiplication *statement) override;
  void Visit(Division *statement) override;
  void Visit(Modulo *statement) override;
  void Visit(Less *statement) override;
  void Visit(Greater *statement) override;
  void Visit(Equal *statement) override;
  void Visit(OrBinary *statement) override;
  void Visit(AndBinary *statement) override;

  void Visit(Assert *statement) override;
  void Visit(Assignment *statement) override;
  void Visit(IfStatement *statement) override;
  void Visit(Return *statement) override;
  void Visit(VariableDeclaration *statement) override;
  void Visit(WhileLoop *statement) override;
  void Visit(Identifier *statement) override;
  void Visit(NotBinary *statement) override;

private:
  int tabulation_length_ = 0;
  std::ofstream fout;
};
