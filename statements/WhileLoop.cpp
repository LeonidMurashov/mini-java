
#include "WhileLoop.h"
#include <visitors/BaseVisitor.h>
void WhileLoop::Accept(BaseVisitor *visitor) { visitor->Visit(this); }

WhileLoop::WhileLoop(BaseExpression *condition, StatementsList *statements)
    : condition(condition), statements(statements) {}
