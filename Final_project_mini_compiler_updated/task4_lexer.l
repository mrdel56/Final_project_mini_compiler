%{
#include "task4_parser.h"
#include <stdio.h>
#include <string.h>

extern int line_num;
extern void yyerror(const char *s);
%}

%option noyywrap

%%

[ \t]+                  { /* Skip whitespace */ }
\n                      { line_num++; }

"#include".*            { /* Ignore C++ preprocessor directives */ }
"using"[ \t]+"namespace".*  { /* Ignore C++ namespace declarations */ }

"//".*                  { /* Single-line comment */ }
"/*"([^*]|\*+[^*/])*"*/" { 
                          for(int i = 0; i < yyleng; i++) {
                              if(yytext[i] == '\n') line_num++;
                          }
                        }

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
