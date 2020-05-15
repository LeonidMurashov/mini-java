
#include "BaseStatement.h"
#include <expressions/BaseExpression.h>
class Print : public BaseStatement {
public:
  explicit Print(BaseExpression *expression, bool endl);
  void Accept(BaseVisitor *visitor) override;

  BaseExpression *expression;
  bool endl;
};
