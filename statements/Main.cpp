
#include "Main.h"
#include <visitors/BaseVisitor.h>
void Main::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
Main::Main(StatementsList *statements) : statements(statements) {}
