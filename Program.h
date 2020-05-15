#pragma once

#include "ASTNode.h"
#include "visitors/forward_decl.h"
#include <vector>

class Program : public ASTNode{
public:
  Program(Main *main_statement) : main_statement(main_statement) {}

private:
  void Accept(BaseVisitor *visitor) override {
    visitor->Visit(this);
  }

public:
  Main *main_statement;
};
