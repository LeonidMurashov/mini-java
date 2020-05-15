#include "driver.hh"
#include "Program.h"
#include "parser.hh"
#include <visitors/Interpreter.h>
#include <visitors/PrintVisitor.h>

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
    variables["one"] = 1;
    variables["two"] = 2;
}


int Driver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end();
    return res;
}

int Driver::exec() {
  PrintVisitor printer("tree.txt");
  printer.Visit(program);

  Interpreter interpreter;
  int ret = interpreter.Visit(program);
//  std::cout << "Exit code " << ret << std::endl;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}
