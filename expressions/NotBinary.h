
#include "BaseExpression.h"
class NotBinary : public BaseExpression{
public:
  explicit NotBinary(BaseExpression *operand);
  void Accept(BaseVisitor *visitor) override;

  BaseExpression *operand{};
};
