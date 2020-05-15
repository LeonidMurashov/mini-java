
#include "BaseExpression.h"
class Constant : public BaseExpression{
public:
  explicit Constant(int value);
  void Accept(BaseVisitor *visitor) override;

  int value = 0;
};
