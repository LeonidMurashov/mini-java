
#include "Return.h"
#include <expressions/BaseExpression.h>
Return::Return(BaseExpression *expression) : expression(expression) {}
void Return::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
