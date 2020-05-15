#include "Print.h"
#include <expressions/BaseExpression.h>

void Print::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
Print::Print(BaseExpression *expression, bool endl)
    : expression(expression), endl(endl) {}
