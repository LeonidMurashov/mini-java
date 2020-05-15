#pragma once

#include "BaseExpression.h"
class BinaryExpression : public BaseExpression{
public:
  BinaryExpression(BaseExpression *left_node, BaseExpression *right_node)
      : left_node(left_node), right_node(right_node) {}

public:
  BaseExpression *left_node{};
  BaseExpression *right_node{};
};
