#pragma once

#include "BinaryExpression.h"

class Division : public BinaryExpression {
public:
  void Accept(BaseVisitor *visitor) override { visitor->Visit(this); }
  using BinaryExpression::BinaryExpression;
};
