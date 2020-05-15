#include "BaseExpression.h"
#include <string>
class Identifier : public BaseExpression{
public:
  explicit Identifier(std::string name);
  void Accept(BaseVisitor *visitor) override;

  std::string name;
};
