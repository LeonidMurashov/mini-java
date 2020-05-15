
#include "BaseStatement.h"
#include <expressions/BaseExpression.h>
#include <string>
class Assert : public BaseStatement {
public:
  void Accept(BaseVisitor *visitor) override;
  Assert(BaseExpression *expression, int lineno);

  BaseExpression *expression{};
  int lineno = 0;
};
