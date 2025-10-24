%{
#include <stdio.h>
#include <string.h>

int line_num = 1;
int token_num = 0;

// Token lists
char keywords[100][20];
char identifiers[100][20];
char constants[100][20];
char arithmetic_ops[100][5];
char logical_ops[100][5];
char punctuation[100][5];
char parenthesis[100][5];

int kw_count = 0, id_count = 0, const_count = 0;
int arith_count = 0, log_count = 0, punct_count = 0, paren_count = 0;

void add_unique_keyword(char *str);
void add_unique_identifier(char *str);
void add_unique_constant(char *str);
void add_unique_operator(char *str, char type);
void add_unique_punct(char *str);
void add_unique_paren(char *str);
void print_token(char *type, char *value);
%}

%option noyywrap

%%

[ \t]+                  { /* Skip whitespace */ }
\n                      { line_num++; }

"int"                   { add_unique_keyword("int"); print_token("KEYWORD", yytext); }
"float"                 { add_unique_keyword("float"); print_token("KEYWORD", yytext); }
"char"                  { add_unique_keyword("char"); print_token("KEYWORD", yytext); }
"double"                { add_unique_keyword("double"); print_token("KEYWORD", yytext); }
"if"                    { add_unique_keyword("if"); print_token("KEYWORD", yytext); }
"else"                  { add_unique_keyword("else"); print_token("KEYWORD", yytext); }
"while"                 { add_unique_keyword("while"); print_token("KEYWORD", yytext); }
"for"                   { add_unique_keyword("for"); print_token("KEYWORD", yytext); }
"return"                { add_unique_keyword("return"); print_token("KEYWORD", yytext); }
"void"                  { add_unique_keyword("void"); print_token("KEYWORD", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { add_unique_identifier(yytext); print_token("IDENTIFIER", yytext); }

[0-9]+                  { add_unique_constant(yytext); print_token("CONSTANT", yytext); }
[0-9]+\.[0-9]+          { add_unique_constant(yytext); print_token("CONSTANT", yytext); }

"+"                     { add_unique_operator("+", 'a'); print_token("ARITHMETIC_OP", yytext); }
"-"                     { add_unique_operator("-", 'a'); print_token("ARITHMETIC_OP", yytext); }
"*"                     { add_unique_operator("*", 'a'); print_token("ARITHMETIC_OP", yytext); }
"/"                     { add_unique_operator("/", 'a'); print_token("ARITHMETIC_OP", yytext); }
"%"                     { add_unique_operator("%", 'a'); print_token("ARITHMETIC_OP", yytext); }

"<"                     { add_unique_operator("<", 'l'); print_token("LOGICAL_OP", yytext); }
">"                     { add_unique_operator(">", 'l'); print_token("LOGICAL_OP", yytext); }
"<="                    { add_unique_operator("<=", 'l'); print_token("LOGICAL_OP", yytext); }
">="                    { add_unique_operator(">=", 'l'); print_token("LOGICAL_OP", yytext); }
"=="                    { add_unique_operator("==", 'l'); print_token("LOGICAL_OP", yytext); }
"!="                    { add_unique_operator("!=", 'l'); print_token("LOGICAL_OP", yytext); }
"&&"                    { add_unique_operator("&&", 'l'); print_token("LOGICAL_OP", yytext); }
"||"                    { add_unique_operator("||", 'l'); print_token("LOGICAL_OP", yytext); }
"!"                     { add_unique_operator("!", 'l'); print_token("LOGICAL_OP", yytext); }

"{"                     { add_unique_paren("{"); print_token("PARENTHESIS", yytext); }
"}"                     { add_unique_paren("}"); print_token("PARENTHESIS", yytext); }
"("                     { add_unique_paren("("); print_token("PARENTHESIS", yytext); }
")"                     { add_unique_paren(")"); print_token("PARENTHESIS", yytext); }
"["                     { add_unique_paren("["); print_token("PARENTHESIS", yytext); }
"]"                     { add_unique_paren("]"); print_token("PARENTHESIS", yytext); }

";"                     { add_unique_punct(";"); print_token("PUNCTUATION", yytext); }
","                     { add_unique_punct(","); print_token("PUNCTUATION", yytext); }
"="                     { add_unique_punct("="); print_token("PUNCTUATION", yytext); }

"//".*                  { /* Ignore single-line comments */ }
"/*"([^*]|\*+[^*/])*"*/"  { 
                          /* Ignore multi-line comments but count newlines */
                          for(int i = 0; i < yyleng; i++) {
                              if(yytext[i] == '\n') line_num++;
                          }
                        }

.                       { printf("ERROR: Unknown character '%s' at line %d\n", yytext, line_num); }

%%

void print_token(char *type, char *value) {
    printf("Token %-3d: %-18s | Value: %-10s | Line: %d\n", ++token_num, type, value, line_num);
}

void add_unique_keyword(char *str) {
    for(int i = 0; i < kw_count; i++) {
        if(strcmp(keywords[i], str) == 0) return;
    }
    strcpy(keywords[kw_count++], str);
}

void add_unique_identifier(char *str) {
    for(int i = 0; i < id_count; i++) {
        if(strcmp(identifiers[i], str) == 0) return;
    }
    strcpy(identifiers[id_count++], str);
}

void add_unique_constant(char *str) {
    for(int i = 0; i < const_count; i++) {
        if(strcmp(constants[i], str) == 0) return;
    }
    strcpy(constants[const_count++], str);
}

void add_unique_operator(char *str, char type) {
    if(type == 'a') {
        for(int i = 0; i < arith_count; i++) {
            if(strcmp(arithmetic_ops[i], str) == 0) return;
        }
        strcpy(arithmetic_ops[arith_count++], str);
    } else {
        for(int i = 0; i < log_count; i++) {
            if(strcmp(logical_ops[i], str) == 0) return;
        }
        strcpy(logical_ops[log_count++], str);
    }
}

void add_unique_punct(char *str) {
    for(int i = 0; i < punct_count; i++) {
        if(strcmp(punctuation[i], str) == 0) return;
    }
    strcpy(punctuation[punct_count++], str);
}

void add_unique_paren(char *str) {
    for(int i = 0; i < paren_count; i++) {
        if(strcmp(parenthesis[i], str) == 0) return;
    }
    strcpy(parenthesis[paren_count++], str);
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    
    printf("===============================================================\n");
    printf("       TASK 1: LEXICAL ANALYSIS (TOKENIZATION)\n");
    printf("===============================================================\n\n");
    
    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            printf("Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
        yyin = input_file;
        printf("Input File: %s\n\n", argv[1]);
    }
    
    printf("TOKEN STREAM:\n");
    printf("---------------------------------------------------------------\n");
    
    yylex();
    
    printf("---------------------------------------------------------------\n");
    printf("Total Tokens Generated: %d\n\n", token_num);
    
    printf("\n===============================================================\n");
    printf("CATEGORIZED TOKENS:\n");
    printf("===============================================================\n\n");
    
    // Keywords
    printf("1. KEYWORDS (%d):\n", kw_count);
    printf("   ");
    for(int i = 0; i < kw_count; i++) {
        printf("%s", keywords[i]);
        if(i < kw_count - 1) printf(", ");
    }
    printf("\n\n");
    
    // Identifiers
    printf("2. IDENTIFIERS (%d):\n", id_count);
    printf("   ");
    for(int i = 0; i < id_count; i++) {
        printf("%s", identifiers[i]);
        if(i < id_count - 1) printf(", ");
    }
    printf("\n\n");
    
    // Constants
    printf("3. CONSTANTS (%d):\n", const_count);
    printf("   ");
    for(int i = 0; i < const_count; i++) {
        printf("%s", constants[i]);
        if(i < const_count - 1) printf(", ");
    }
    printf("\n\n");
    
    // Arithmetic Operators
    printf("4. ARITHMETIC OPERATORS (%d):\n", arith_count);
    printf("   ");
    for(int i = 0; i < arith_count; i++) {
        printf("%s", arithmetic_ops[i]);
        if(i < arith_count - 1) printf(", ");
    }
    printf("\n\n");
    
    // Logical Operators
    printf("5. LOGICAL OPERATORS (%d):\n", log_count);
    if(log_count > 0) {
        printf("   ");
        for(int i = 0; i < log_count; i++) {
            printf("%s", logical_ops[i]);
            if(i < log_count - 1) printf(", ");
        }
        printf("\n\n");
    } else {
        printf("   None\n\n");
    }
    
    // Punctuation
    printf("6. PUNCTUATION (%d):\n", punct_count);
    printf("   ");
    for(int i = 0; i < punct_count; i++) {
        printf("%s", punctuation[i]);
        if(i < punct_count - 1) printf(", ");
    }
    printf("\n\n");
    
    // Parenthesis
    printf("7. PARENTHESIS/BRACKETS (%d):\n", paren_count);
    printf("   ");
    for(int i = 0; i < paren_count; i++) {
        printf("%s", parenthesis[i]);
        if(i < paren_count - 1) printf(", ");
    }
    printf("\n\n");
    
    printf("===============================================================\n");
    printf("✓ Lexical Analysis completed successfully!\n");
    printf("===============================================================\n");
    
    if (argc > 1) fclose(input_file);
    
    return 0;
}
