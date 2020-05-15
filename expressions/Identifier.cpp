
#include "Identifier.h"
#include <string>
Identifier::Identifier(std::string name) : name(std::move(name)) {}
void Identifier::Accept(BaseVisitor *visitor) { visitor->Visit(this); }
