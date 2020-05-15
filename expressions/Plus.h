#pragma once

#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
  void Accept(BaseVisitor *visitor) override { visitor->Visit(this); }
  using BinaryExpression::BinaryExpression;
};
