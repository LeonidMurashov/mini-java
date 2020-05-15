
#include "Interpreter.h"
#include "elements.h"
#include <iostream>

void Interpreter::Visit(Assert *statement) {
  statement->expression->Accept(this);
  if (!tos_value) {
    throw std::runtime_error("Assertion at line " +
                             std::to_string(statement->lineno));
  }
}
void Interpreter::Visit(Assignment *statement) {
  statement->expression->Accept(this);
  global_scope_[statement->name] = tos_value;
}
void Interpreter::Visit(IfStatement *statement) {
  statement->condition->Accept(this);
  if (tos_value) {
    statement->statements_then->Accept(this);
  } else if (statement->statements_else) {
    statement->statements_else->Accept(this);
  }
}
void Interpreter::Visit(Main *statement) {
  statement->statements->Accept(this);
}
void Interpreter::Visit(Print *statement) {
  statement->expression->Accept(this);
  std::cout << tos_value;
  if (statement->endl){
    std::cout << std::endl;
  }
}
void Interpreter::Visit(Return *statement) {
  statement->expression->Accept(this);
  throw std::runtime_error("Program exited with code " +
                           std::to_string(tos_value));
}
void Interpreter::Visit(StatementsList *list) {
  for (auto stmt : list->list) {
    stmt->Accept(this);
  }
}
void Interpreter::Visit(VariableDeclaration *statement) {
  statement->expression->Accept(this);
  global_scope_[statement->name] = tos_value;
}
void Interpreter::Visit(WhileLoop *statement) {
  statement->condition->Accept(this);
  while (tos_value) {
    statement->statements->Accept(this);
    statement->condition->Accept(this);
  }
}
void Interpreter::Visit(AndBinary *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = tos_value && val;
}
void Interpreter::Visit(Constant *number) { tos_value = number->value; }
void Interpreter::Visit(Division *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = val / tos_value;
}
void Interpreter::Visit(Equal *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = tos_value == val;
}
void Interpreter::Visit(Greater *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = val > tos_value;
}
void Interpreter::Visit(Identifier *statement) {
  tos_value = global_scope_[statement->name];
}
void Interpreter::Visit(Less *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = val < tos_value;
}
void Interpreter::Visit(Minus *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = val - tos_value;
}
void Interpreter::Visit(Modulo *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = val % tos_value;
}
void Interpreter::Visit(Multiplication *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value *= val;
}
void Interpreter::Visit(NotBinary *statement) {
  statement->operand->Accept(this);
  tos_value = tos_value ? 1 : 0;
}
void Interpreter::Visit(OrBinary *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value = tos_value || val;
}
void Interpreter::Visit(Plus *statement) {
  statement->left->Accept(this);
  int val = tos_value;
  statement->right->Accept(this);
  tos_value += val;
}

int Interpreter::Visit(Program *program) {
  program->main_statement->Accept(this);
  return tos_value;
}
