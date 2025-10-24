%{
#include "task5_parser.h"
#include <stdio.h>
#include <string.h>

extern int line_num;
extern void yyerror(const char *s);
%}

%option noyywrap

%%

[ \t]+                  { /* Skip whitespace */ }
\n                      { line_num++; }

"//".*                  { /* Single-line comment */ }
"/*"([^*]|\*+[^*/])*"*/" { 
                          for(int i = 0; i < yyleng; i++) {
                              if(yytext[i] == '\n') line_num++;
                          }
                        }

"#include"[ \t]*"<"[^>]*">"  { /* Ignore #include <...> */ }
"#include"[ \t]*"\""[^\"]*"\"" { /* Ignore #include "..." */ }
"using"[ \t]+"namespace"[ \t]+"std"[ \t]*";" { /* Ignore using namespace std; */ }

"cout"                  { /* Ignore cout */ }
"cin"                   { /* Ignore cin */ }
"<<"                    { /* Ignore << */ }
">>"                    { /* Ignore >> */ }
"endl"                  { /* Ignore endl */ }

"int"                   { return INT; }
"float"                 { return FLOAT; }
"char"                  { return CHAR; }
"double"                { return DOUBLE; }
"void"                  { return VOID; }
"if"                    { return IF; }
"else"                  { return ELSE; }
"while"                 { return WHILE; }
"for"                   { return FOR; }
"return"                { return RETURN; }

[a-zA-Z_][a-zA-Z0-9_]*  { 
                          yylval.str = strdup(yytext); 
                          return ID; 
                        }

[0-9]+                  { 
                          yylval.num = atoi(yytext); 
                          return NUM; 
                        }

[0-9]+\.[0-9]+          { 
                          yylval.fnum = atof(yytext); 
                          return FLOAT_NUM; 
                        }

"\""[^\"]*"\""          { /* Ignore string literals */ }

"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MUL; }
"/"                     { return DIV; }
"="                     { return ASSIGN; }

"<"                     { return LT; }
">"                     { return GT; }
"<="                    { return LE; }
">="                    { return GE; }
"=="                    { return EQ; }
"!="                    { return NE; }

"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"["                     { return LBRACKET; }
"]"                     { return RBRACKET; }
";"                     { return SEMI; }
","                     { return COMMA; }

.                       { /* Ignore unknown characters */ }

%%
