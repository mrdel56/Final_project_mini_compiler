%{
#include "task3_parser.h"
#include <stdio.h>
#include <string.h>

extern int line_num;
extern void yyerror(const char *s);

int token_count = 0;
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

"int"                   { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return INT; }
"float"                 { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return FLOAT; }
"char"                  { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return CHAR; }
"double"                { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return DOUBLE; }
"void"                  { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return VOID; }
"if"                    { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return IF; }
"else"                  { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return ELSE; }
"while"                 { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return WHILE; }
"for"                   { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return FOR; }
"return"                { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "KEYWORD", yytext, line_num); return RETURN; }

[a-zA-Z_][a-zA-Z0-9_]*  { 
                          printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "IDENTIFIER", yytext, line_num);
                          yylval.str = strdup(yytext); 
                          return ID; 
                        }

[0-9]+                  { 
                          printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "CONSTANT", yytext, line_num);
                          yylval.num = atoi(yytext); 
                          return NUM; 
                        }

[0-9]+\.[0-9]+          { 
                          printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "CONSTANT", yytext, line_num);
                          yylval.fnum = atof(yytext); 
                          return FLOAT_NUM; 
                        }

"+"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "ARITHMETIC_OP", yytext, line_num); return PLUS; }
"-"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "ARITHMETIC_OP", yytext, line_num); return MINUS; }
"*"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "ARITHMETIC_OP", yytext, line_num); return MUL; }
"/"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "ARITHMETIC_OP", yytext, line_num); return DIV; }

"<"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "LOGICAL_OP", yytext, line_num); return LT; }
">"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "LOGICAL_OP", yytext, line_num); return GT; }
"<="                    { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "LOGICAL_OP", yytext, line_num); return LE; }
">="                    { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "LOGICAL_OP", yytext, line_num); return GE; }
"=="                    { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "LOGICAL_OP", yytext, line_num); return EQ; }
"!="                    { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "LOGICAL_OP", yytext, line_num); return NE; }

"{"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PARENTHESIS", yytext, line_num); return LBRACE; }
"}"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PARENTHESIS", yytext, line_num); return RBRACE; }
"("                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PARENTHESIS", yytext, line_num); return LPAREN; }
")"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PARENTHESIS", yytext, line_num); return RPAREN; }
"["                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PARENTHESIS", yytext, line_num); return LBRACKET; }
"]"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PARENTHESIS", yytext, line_num); return RBRACKET; }

";"                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PUNCTUATION", yytext, line_num); return SEMI; }
","                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PUNCTUATION", yytext, line_num); return COMMA; }
"="                     { printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_count, "PUNCTUATION", yytext, line_num); return ASSIGN; }

.                       { /* Ignore unknown characters silently */ }

%%
