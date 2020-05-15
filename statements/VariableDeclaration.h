
#include "BaseStatement.h"
#include <expressions/BaseExpression.h>
#include <string>
class VariableDeclaration : public BaseStatement {
public:
  VariableDeclaration(std::string name, BaseExpression *expression);
  void Accept(BaseVisitor *visitor) override;

  std::string name{};
  BaseExpression *expression{};
};
