
#include "Assert.h"
#include <visitors/BaseVisitor.h>
void Assert::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
Assert::Assert(BaseExpression *expression, int lineno)
    : expression(expression), lineno(lineno) {}
