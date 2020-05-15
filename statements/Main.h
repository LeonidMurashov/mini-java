#pragma once

#include "BaseStatement.h"
#include <visitors/BaseVisitor.h>
class Main : public BaseStatement {
public:
  explicit Main(StatementsList *statements);
  void Accept(BaseVisitor *visitor) override;
  StatementsList *statements{};
};
