
#include "BaseStatement.h"
#include <expressions/BaseExpression.h>
#include <string>
class WhileLoop : public BaseStatement {
public:
  void Accept(BaseVisitor *visitor) override;
  WhileLoop(BaseExpression *condition, StatementsList *statements);
  BaseExpression *condition{};
  StatementsList *statements{};
};
