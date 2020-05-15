
#include "Constant.h"
#include <visitors/BaseVisitor.h>
void Constant::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
Constant::Constant(int value) : value(value) {}
