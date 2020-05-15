%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug yylineno

%option c++
%option yyclass="Scanner"

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"-"        {
              return yy::parser::make_MINUS  (loc);
           }
"+"        return yy::parser::make_PLUS   (loc);
"*"        return yy::parser::make_STAR   (loc);
"/"        return yy::parser::make_SLASH  (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
"{"        return yy::parser::make_LCURLBRACKET (loc);
"}"        return yy::parser::make_RCURLBRACKET (loc);
"="        return yy::parser::make_ASSIGN (loc);
"int"      return yy::parser::make_INT_TYPE (loc);
";"        return yy::parser::make_SEMICOLON (loc);
"System.out.println"       return yy::parser::make_PRINTLN (loc);
"System.out.print"       return yy::parser::make_PRINT (loc);
"public static void main"  return yy::parser::make_PSVM (loc);
"class"    return yy::parser::make_CLASS (loc);
"%"        return yy::parser::make_PERCENT (loc);
"&&"        return yy::parser::make_AND (loc);
"||"        return yy::parser::make_OR (loc);
"=="        return yy::parser::make_EQUALS (loc);
">"        return yy::parser::make_GREATER (loc);
"<"        return yy::parser::make_LESS (loc);
"!"        return yy::parser::make_EXCLAMATION (loc);
"return"        return yy::parser::make_RETURN (loc);
"while"        return yy::parser::make_WHILE (loc);
"if"        return yy::parser::make_IF (loc);
"true"        return yy::parser::make_TRUE (loc);
"false"        return yy::parser::make_FALSE (loc);
"this"        return yy::parser::make_THIS (loc);
"assert"        return yy::parser::make_ASSERT (loc);
"else"        return yy::parser::make_ELSE (loc);


{int}      return make_NUMBER(yytext, loc);
{id}       return yy::parser::make_IDENTIFIER(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}