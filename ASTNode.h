#pragma once
#include <visitors/BaseVisitor.h>
class ASTNode {
public:
  virtual void Accept(BaseVisitor* visitor) = 0;
  virtual ~ASTNode() = default;
};
