#pragma once

#include "BaseExpression.h"
class BinaryExpression : public BaseExpression{
public:
  BinaryExpression(BaseExpression *left_node, BaseExpression *right_node)
      : left(left_node), right(right_node) {}

public:
  BaseExpression *left{};
  BaseExpression *right{};
};
