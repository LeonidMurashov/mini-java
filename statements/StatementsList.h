
#include "BaseStatement.h"
#include <vector>
class StatementsList : public BaseStatement{
public:
  void AddStatement(BaseStatement *statement);
  void Accept(BaseVisitor *visitor) override;

  std::vector<BaseStatement*> list;
};
