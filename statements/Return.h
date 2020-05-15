
#include "BaseStatement.h"
#include <expressions/BaseExpression.h>
class Return : public BaseStatement {
public:
  void Accept(BaseVisitor *visitor) override;
  explicit Return(BaseExpression *expression);
  BaseExpression *expression;
};
