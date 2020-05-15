#include "PrintVisitor.h"
#include <iostream>

#include "elements.h"

using std::endl;
using std::string;

string MakeTabulation(int tabulation_size) {
  string tabs;
  for (int i = 0; i < tabulation_size; ++i) {
    tabs += "  ";
  }
  return tabs;
}

template <class T> void PrintVisitor::VisitTerminal(T terminal) {
  fout << MakeTabulation(tabulation_length_) << terminal << endl;
}

void PrintVisitor::VisitUnary(const std::string &name, ASTNode *arg) {
  fout << MakeTabulation(tabulation_length_) << name << endl;
  tabulation_length_++;
  arg->Accept(this);
  tabulation_length_--;
}

void PrintVisitor::VisitBinary(const std::string &name, ASTNode *left,
                               ASTNode *right) {
  fout << MakeTabulation(tabulation_length_) << name << endl;
  tabulation_length_++;
  left->Accept(this);
  right->Accept(this);
  tabulation_length_--;
}

void PrintVisitor::VisitTernary(const std::string &name, ASTNode *first,
                                ASTNode *second, ASTNode *third) {
  fout << MakeTabulation(tabulation_length_) << name << endl;
  tabulation_length_++;
  first->Accept(this);
  second->Accept(this);
  third->Accept(this);
  tabulation_length_--;
}

void PrintVisitor::Visit(StatementsList *list) {
  for (auto stmt : list->list) {
    stmt->Accept(this);
  }
}

int PrintVisitor::Visit(Program *program) {
  VisitUnary("Program", program->main_statement);
  return 0;
}

void PrintVisitor::Visit(Main *statement) {
  VisitUnary("main()", statement->statements);
}
void PrintVisitor::Visit(Constant *number) { VisitTerminal(number->value); }
void PrintVisitor::Visit(Print *statement) {
  VisitUnary("Print()", statement->expression);
}

void PrintVisitor::Visit(Plus *statement) {
  VisitBinary("+", statement->left, statement->right);
}
void PrintVisitor::Visit(Minus *statement) {
  VisitBinary("-", statement->left, statement->right);
}
void PrintVisitor::Visit(Multiplication *statement) {
  VisitBinary("*", statement->left, statement->right);
}
void PrintVisitor::Visit(Division *statement) {
  VisitBinary("/", statement->left, statement->right);
}
void PrintVisitor::Visit(Modulo *statement) {
  VisitBinary("%", statement->left, statement->right);
}
void PrintVisitor::Visit(Less *statement) {
  VisitBinary("<", statement->left, statement->right);
}
void PrintVisitor::Visit(Greater *statement) {
  VisitBinary(">", statement->left, statement->right);
}
void PrintVisitor::Visit(Equal *statement) {
  VisitBinary("==", statement->left, statement->right);
}
void PrintVisitor::Visit(OrBinary *statement) {
  VisitBinary("||", statement->left, statement->right);
}
void PrintVisitor::Visit(AndBinary *statement) {
  VisitBinary("&&", statement->left, statement->right);
}
void PrintVisitor::Visit(Assert *statement) {
  VisitUnary("Assert in line: " + std::to_string(statement->lineno),
             statement->expression);
}
void PrintVisitor::Visit(Assignment *statement) {
  VisitUnary(statement->name + " =", statement->expression);
}

void PrintVisitor::Visit(Return *statement) {
  VisitUnary("Return", statement->expression);
}
void PrintVisitor::Visit(VariableDeclaration *statement) {
  VisitUnary("Declare: " + statement->name + " =", statement->expression);
}
void PrintVisitor::Visit(Identifier *statement) {
  VisitTerminal(statement->name);
}
void PrintVisitor::Visit(NotBinary *statement) {
  VisitUnary("!", statement->operand);
}

void PrintVisitor::Visit(IfStatement *statement) {
  fout << MakeTabulation(tabulation_length_) << "if (" << endl;
  tabulation_length_++;
  statement->condition->Accept(this);
  tabulation_length_--;

  fout << MakeTabulation(tabulation_length_) << ") {" << endl;
  tabulation_length_++;
  statement->statements_then->Accept(this);
  tabulation_length_--;
  fout << MakeTabulation(tabulation_length_) << "} else {" << endl;

  if (statement->statements_else) {
    tabulation_length_++;
    statement->statements_else->Accept(this);
    tabulation_length_--;
  }

  fout << MakeTabulation(tabulation_length_) << "}" << endl;
}
void PrintVisitor::Visit(WhileLoop *statement) {
  fout << MakeTabulation(tabulation_length_) << "while (" << endl;
  tabulation_length_++;
  statement->condition->Accept(this);
  tabulation_length_--;

  fout << MakeTabulation(tabulation_length_) << ") {" << endl;
  tabulation_length_++;
  statement->statements->Accept(this);
  tabulation_length_--;

  fout << MakeTabulation(tabulation_length_) << "}" << endl;
}
