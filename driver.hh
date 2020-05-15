#pragma once

#include "Program.h"
#include "parser.hh"
#include "scanner.h"
#include <fstream>
#include <map>
#include <string>

class Driver {
public:
  Driver();
  std::map<std::string, int> variables;
  int return_code;
  int parse(const std::string &f);
  int exec();
  std::string file;
  bool trace_parsing;

  void scan_begin();
  void scan_end();

  bool trace_scanning;
  yy::location location;

  friend class Scanner;
  Scanner scanner;
  yy::parser parser;

  Program *program;

private:
  std::ifstream stream;
};
