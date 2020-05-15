%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include "visitors/elements.h"

    class Scanner;
    class Driver;
    #include "visitors/forward_decl.h"
    #include "Program.h"
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
    PRINT "System.out.print"
    PSVM "public static void main"
    CLASS "class"
    RETURN "return"
    WHILE "while"
    IF "if"
    ELSE "else"
    TRUE "true"
    FALSE "false"
    THIS "this"
    ASSERT "assert"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <Program*> program
%nterm <BaseStatement*> statement
%nterm <StatementsList*> statements
%nterm <StatementsList*> bracketed_statements
%nterm <Main*> main_class
%nterm <BaseExpression*> expr
%nterm <BinaryExpression*> binary_operation
%nterm <VariableDeclaration*> variable_declaration

%printer { yyo << $$; } <*>;

%%
%start program;

program:
    main_class { $$ = new Program($1); driver.program = $$; }

main_class:
    "class" "identifier" "{" "public static void main" "(" ")" "{" statements "}" "}" {
        $$ = new Main($8);
    }


//class_declaration:
//declaration:
//method_declaration:
//formals

statement:
    "assert" "(" expr ")" ";" { $$ = new Assert($3, scanner.lineno()); }
    | variable_declaration { $$ = $1; }
    | "{" statements "}" { $$ = $2; }
    | "if"  "(" expr ")" bracketed_statements { $$ = new IfStatement($3, $5, nullptr); }
    | "if"  "(" expr ")" bracketed_statements "else" bracketed_statements
        { $$ = new IfStatement($3, $5, $7); }
    | "while"  "(" expr ")" bracketed_statements { $$ = new WhileLoop($3, $5); }
    | "System.out.println" "(" expr ")" ";" { $$ = new Print($3, true); }
    | "System.out.print" "(" expr ")" ";" { $$ = new Print($3, false); }
    | "identifier" "=" expr ";" { $$ = new Assignment($1, $3); }
    | "return" expr ";" { $$ = new Return($2); }
//    | method_invocation ";" {}
    | statements { $$ = $1; }

bracketed_statements:
    "{" statements "}" { $$ = $2; }

statements:
    %empty { $$ = new StatementsList(); }
    | statements statement { $1->AddStatement($2); $$ = $1; }

variable_declaration:
    "int" "identifier" ";" { $$ = new VariableDeclaration($2, 0); }
    | "int" "identifier" "=" expr ";" { $$ = new VariableDeclaration($2, $4); }

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
    | "!" expr { $$ = new NotBinary($2); }
    | "(" expr ")" { $$ = $2; }
    | "identifier" { $$ = new Identifier($1); }
    | "number" { $$ = new Constant($1); }
    | "this" {}
    | "true" { $$ = new Constant(1); }
    | "false" { $$ = new Constant(0); }
//    | method_invocation {}

%left "||";
%left "&&";
%left ">" "<" "==";
%left "+" "-";
%left "*" "/" "%";

binary_operation:
      expr "+" expr  { $$ = new Plus($1, $3); }
    | expr "-" expr  { $$ = new Minus($1, $3); }
    | expr "*" expr  { $$ = new Multiplication($1, $3); }
    | expr "/" expr  { $$ = new Division($1, $3); }
    | expr "%" expr  { $$ = new Modulo($1, $3); }
    | expr "<" expr  { $$ = new Less($1, $3); }
    | expr ">" expr  { $$ = new Greater($1, $3); }
    | expr "==" expr  { $$ = new Equal($1, $3); }
    | expr "||" expr  { $$ = new OrBinary($1, $3); }
    | expr "&&" expr  { $$ = new AndBinary($1, $3); }
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
