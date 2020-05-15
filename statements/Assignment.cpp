
#include "Assignment.h"
#include <visitors/BaseVisitor.h>

#include <utility>
void Assignment::Accept(BaseVisitor *visitor) {
  visitor->Visit(this);
}

Assignment::Assignment(std::string name, BaseExpression *expression)
    : name(std::move(name)), expression(expression) {}
