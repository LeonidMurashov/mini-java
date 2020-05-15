
#include "BaseStatement.h"
#include <expressions/BaseExpression.h>
#include <string>
class Assignment : public BaseStatement {
public:
  void Accept(BaseVisitor *visitor) override;
  Assignment(std::string name, BaseExpression *expression);
  std::string name;
  BaseExpression *expression;
};
