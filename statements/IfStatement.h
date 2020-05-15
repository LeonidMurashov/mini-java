
#include "BaseStatement.h"
#include <expressions/BaseExpression.h>
#include <string>
class IfStatement : public BaseStatement {
public:
  void Accept(BaseVisitor *visitor) override;
  IfStatement(BaseExpression *condition, StatementsList *statements_then,
              StatementsList *statements_else);
  BaseExpression *condition{};
  StatementsList *statements_then{};
  StatementsList *statements_else{};
};
