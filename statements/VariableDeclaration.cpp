#include "VariableDeclaration.h"
#include <visitors/BaseVisitor.h>

#include <utility>

void VariableDeclaration::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
VariableDeclaration::VariableDeclaration(std::string name,
                                         BaseExpression *expression)
    : name(std::move(name)), expression(expression) {}
