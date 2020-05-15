
#include "NotBinary.h"
NotBinary::NotBinary(BaseExpression *operand) : operand(operand) {}
void NotBinary::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
