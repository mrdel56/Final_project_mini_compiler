%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern FILE *yyin;
extern int token_count;

int line_num = 1;
int syntax_error_count = 0;
int semantic_error_count = 0;
int parse_success = 1;

// Track reported errors to avoid duplicates
char reported_errors[100][100];
int reported_error_count = 0;

// Symbol Table
typedef struct {
    char name[50];
    char type[20];
    char lines[200];
    int is_function;
} Symbol;

Symbol symbol_table[100];
int symbol_count = 0;

void yyerror(const char *s);
void semantic_error(const char *msg, char *name);
int is_error_reported(char *name, int line);
void add_symbol(char *name, char *type, int is_function);
void update_symbol_line(char *name);
int lookup_symbol(char *name);
int check_declaration(char *name);
void print_symbol_table();
void print_analysis_summary();
%}

%union {
    int num;
    float fnum;
    char *str;
}

%token <num> NUM
%token <fnum> FLOAT_NUM
%token <str> ID
%token INT FLOAT CHAR DOUBLE VOID
%token IF ELSE WHILE FOR RETURN
%token PLUS MINUS MUL DIV ASSIGN
%token LT GT LE GE EQ NE
%token LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET SEMI COMMA

%type <str> type

%left PLUS MINUS
%left MUL DIV
%nonassoc LT GT LE GE EQ NE

%%

program:
    function_list
    ;

function_list:
    function_list function
    | function
    ;

function:
    type ID LPAREN param_list RPAREN LBRACE stmt_list RBRACE {
        add_symbol($2, $1, 1);
    }
    | type ID LPAREN RPAREN LBRACE stmt_list RBRACE {
        add_symbol($2, $1, 1);
    }
    ;

param_list:
    param_list COMMA type ID { add_symbol($4, $3, 0); }
    | type ID { add_symbol($2, $1, 0); }
    ;

type:
    INT { $$ = strdup("int"); }
    | FLOAT { $$ = strdup("float"); }
    | CHAR { $$ = strdup("char"); }
    | DOUBLE { $$ = strdup("double"); }
    | VOID { $$ = strdup("void"); }
    ;

stmt_list:
    stmt_list stmt
    | /* empty */
    ;

stmt:
    declaration
    | assignment
    | if_stmt
    | while_stmt
    | return_stmt
    | error SEMI { 
        yyerrok; 
    }
    ;

declaration:
    type ID SEMI { add_symbol($2, $1, 0); }
    | type ID LBRACKET NUM RBRACKET SEMI { add_symbol($2, $1, 0); }
    | type ID LBRACKET NUM RBRACKET LBRACKET NUM RBRACKET SEMI { add_symbol($2, $1, 0); }
    | type ID ASSIGN expr SEMI { add_symbol($2, $1, 0); }
    ;

assignment:
    ID ASSIGN expr SEMI { 
        if(!check_declaration($1) && !is_error_reported($1, line_num)) {
            semantic_error("Undeclared variable", $1);
        }
        update_symbol_line($1); 
    }
    | ID LBRACKET expr RBRACKET ASSIGN expr SEMI { 
        if(!check_declaration($1) && !is_error_reported($1, line_num)) {
            semantic_error("Undeclared array", $1);
        }
        update_symbol_line($1); 
    }
    ;

if_stmt:
    IF LPAREN condition RPAREN LBRACE stmt_list RBRACE
    | IF LPAREN condition RPAREN LBRACE stmt_list RBRACE ELSE LBRACE stmt_list RBRACE
    ;

while_stmt:
    WHILE LPAREN condition RPAREN LBRACE stmt_list RBRACE
    ;

return_stmt:
    RETURN expr SEMI
    | RETURN SEMI
    ;

condition:
    expr relop expr
    ;

relop:
    LT | GT | LE | GE | EQ | NE
    ;

expr:
    expr PLUS term
    | expr MINUS term
    | term
    ;

term:
    term MUL factor
    | term DIV factor
    | factor
    ;

factor:
    LPAREN expr RPAREN
    | ID { 
        if(!check_declaration($1) && !is_error_reported($1, line_num)) {
            semantic_error("Undeclared variable", $1);
        }
        update_symbol_line($1); 
    }
    | NUM
    | FLOAT_NUM
    | ID LBRACKET expr RBRACKET { 
        if(!check_declaration($1) && !is_error_reported($1, line_num)) {
            semantic_error("Undeclared array", $1);
        }
        update_symbol_line($1); 
    }
    ;

%%

void yyerror(const char *s) {
    syntax_error_count++;
    parse_success = 0;
    fprintf(stderr, "\n❌ SYNTAX ERROR at line %d: %s\n\n", line_num, s);
}

int is_error_reported(char *name, int line) {
    char key[100];
    sprintf(key, "%s_%d", name, line);
    
    for(int i = 0; i < reported_error_count; i++) {
        if(strcmp(reported_errors[i], key) == 0) {
            return 1;
        }
    }
    
    strcpy(reported_errors[reported_error_count++], key);
    return 0;
}

void semantic_error(const char *msg, char *name) {
    semantic_error_count++;
    parse_success = 0;
    fprintf(stderr, "\n❌ SEMANTIC ERROR at line %d: %s '%s'\n\n", line_num, msg, name);
}

int lookup_symbol(char *name) {
    for(int i = 0; i < symbol_count; i++) {
        if(strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int check_declaration(char *name) {
    return (lookup_symbol(name) != -1);
}

void add_symbol(char *name, char *type, int is_function) {
    int idx = lookup_symbol(name);
    if(idx != -1) {
        char line_str[10];
        sprintf(line_str, "%d", line_num);
        if(strstr(symbol_table[idx].lines, line_str) == NULL) {
            strcat(symbol_table[idx].lines, ", ");
            strcat(symbol_table[idx].lines, line_str);
        }
        return;
    }
    
    strcpy(symbol_table[symbol_count].name, name);
    strcpy(symbol_table[symbol_count].type, type);
    sprintf(symbol_table[symbol_count].lines, "%d", line_num);
    symbol_table[symbol_count].is_function = is_function;
    symbol_count++;
}

void update_symbol_line(char *name) {
    int idx = lookup_symbol(name);
    if(idx != -1) {
        char line_str[10];
        sprintf(line_str, "%d", line_num);
        
        if(strstr(symbol_table[idx].lines, line_str) == NULL) {
            strcat(symbol_table[idx].lines, ", ");
            strcat(symbol_table[idx].lines, line_str);
        }
    }
}

void print_symbol_table() {
    printf("\n===============================================================\n");
    printf("                    SYMBOL TABLE\n");
    printf("===============================================================\n\n");
    printf("%-20s %-15s %-10s %-20s\n", "NAME", "TYPE", "KIND", "LINES");
    printf("---------------------------------------------------------------\n");
    
    for(int i = 0; i < symbol_count; i++) {
        char *kind = symbol_table[i].is_function ? "Function" : "Variable";
        printf("%-20s %-15s %-10s %-20s\n",
               symbol_table[i].name,
               symbol_table[i].type,
               kind,
               symbol_table[i].lines);
    }
    
    printf("---------------------------------------------------------------\n");
    printf("Total Symbols: %d\n", symbol_count);
    printf("===============================================================\n");
}

void print_analysis_summary() {
    printf("\n===============================================================\n");
    printf("           SYNTAX & SEMANTIC ANALYSIS SUMMARY\n");
    printf("===============================================================\n");
    
    printf("\nTotal Tokens Generated: %d\n", token_count);
    printf("Total Syntax Errors: %d\n", syntax_error_count);
    printf("Total Semantic Errors: %d\n", semantic_error_count);
    
    if(parse_success && semantic_error_count == 0 && syntax_error_count == 0) {
        printf("\n✓✓ Status: ANALYSIS SUCCESSFUL\n");
        printf("✓ No syntax errors detected\n");
        printf("✓ No semantic errors detected\n");
    } else {
        printf("\n❌ Status: ANALYSIS FAILED\n");
        if(syntax_error_count > 0) {
            printf("❌ Syntax errors found: %d\n", syntax_error_count);
        }
        if(semantic_error_count > 0) {
            printf("❌ Semantic errors found: %d\n", semantic_error_count);
        }
    }
    
    printf("\n===============================================================\n");
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    
    printf("===============================================================\n");
    printf("     TASK 3 & 4: SYNTAX & SEMANTIC ANALYSIS\n");
    printf("===============================================================\n\n");
    
    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            printf("Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
        yyin = input_file;
        printf("Input File: %s\n\n", argv[1]);
    } else {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    printf("TOKEN STREAM:\n");
    printf("---------------------------------------------------------------\n");
    
    yyparse();
    
    printf("---------------------------------------------------------------\n");
    
    print_symbol_table();
    print_analysis_summary();
    
    if (argc > 1) fclose(input_file);
    
    return 0;
}
