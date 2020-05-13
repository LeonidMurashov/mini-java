%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    ASSIGN "="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    PERCENT "%"
    AND "&&"
    OR "||"
    EQUALS "=="
    GREATER ">"
    LESS "<"
    LPAREN "("
    RPAREN ")"
    LCURLBRACKET "{"
    RCURLBRACKET "}"
    EXCLAMATION "!"
    SEMICOLON ";"
    INT_TYPE "int"
    PRINTLN "System.out.println"
    PSVM "public static void main"
    CLASS "class"
    RETURN "return"
    WHILE "while"
    IF "if"
    TRUE "true"
    FALSE "false"
    THIS "this"
    ASSERT "assert"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <int> statement
%nterm <int> main_class
%nterm <int> expr
%nterm <int> binary_operation

%printer { yyo << $$; } <*>;

%%
%start program;

program:
    main_class {}

main_class:
    "class" "identifier" "{" "public static void main" "(" ")" "{" statement "}" "}" {}


//class_declaration:
//declaration:
//method_declaration:
//formals

statement:
    "assert" "(" expr ")" ";" {
        if (!$3) {
            std::cout << "Assertion at line " << scanner.lineno() << std::endl;
            driver.return_code = 1;
            YYACCEPT;
        }
    }
    | variable_declaration {}
    | "{" statement "}" {}
    | "if"  "(" expr ")" statement {}
    | "if"  "(" expr ")" statement "else" statement {}
    | "while"  "(" expr ")" statement {}
    | "System.out.println" "(" expr ")" ";" { std::cout << $3 << std::endl; }
    | "identifier" "=" expr ";" { driver.variables[$1] = $3; }
    | "return" expr ";" { driver.return_code = $2; YYACCEPT; }
//    | method_invocation ";" {}
    | statement statement {}

variable_declaration:
    "int" "identifier" ";" { driver.variables[$2] = 0; }

//method_invocation:
//	expr "." "identifier" "(" [ expr ("," expr)* ] ")" {}

//lvalue:
//    "identifier"
//    | "identifier" "[" expr "]" {}

expr:
    binary_operation { $$ = $1; }
    | expr "[" expr "]" {}
    | expr "." "length" {}
    | "new" "int" "[" expr "]" {}
    | "!" expr { $$ = !$2; }
    | "(" expr ")" { $$ = $2; }
    | "identifier" { $$ = driver.variables[$1]; }
    | "number" { $$ = $1; }
    | "this" {}
    | "true" { $$ = 1; }
    | "false" { $$ = 0; }
//    | method_invocation {}

%left "||";
%left "&&";
%left ">" "<" "==";
%left "+" "-";
%left "*" "/" "%";

binary_operation:
	  expr "&&" expr { $$ = $1 && $3; }
	| expr "||" expr { $$ = $1 || $3; }
	| expr "<" expr  { $$ = $1 < $3; }
	| expr ">" expr  { $$ = $1 > $3; }
	| expr "==" expr { $$ = $1 == $3; }
	| expr "+" expr  { $$ = $1 + $3; }
	| expr "-" expr  { $$ = $1 - $3; }
	| expr "*" expr  { $$ = $1 * $3; }
	| expr "/" expr  { $$ = $1 / $3; }
	| expr "%" expr  { $$ = $1 % $3; }

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
