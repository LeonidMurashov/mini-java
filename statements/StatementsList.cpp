
#include "StatementsList.h"
void StatementsList::AddStatement(BaseStatement *statement) {
  list.push_back(statement);
}
void StatementsList::Accept(BaseVisitor *visitor) {
  visitor->Visit(this);
}
