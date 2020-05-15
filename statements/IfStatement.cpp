
#include "IfStatement.h"
#include <visitors/BaseVisitor.h>
void IfStatement::Accept(BaseVisitor *visitor) { visitor->Visit(this); }

IfStatement::IfStatement(BaseExpression *condition,
                         StatementsList *statements_then,
                         StatementsList *statements_else)
    : condition(condition), statements_then(statements_then),
      statements_else(statements_else) {}
