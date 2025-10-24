%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern FILE *yyin;

int line_num = 1;
int address_counter = 1000;

// AST Node Structure
typedef struct ASTNode {
    char type[50];
    char value[50];
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
} ASTNode;

// Symbol Table
typedef struct {
    char name[50];
    char type[20];
    int size;
    int dimension;
    char array_spec[20];
    char lines[200];
    int address;
} Symbol;

Symbol symbol_table[100];
int symbol_count = 0;

ASTNode *root = NULL;

void yyerror(const char *s);
ASTNode* create_node(char *type, char *value, ASTNode *left, ASTNode *right);
void print_ast(ASTNode *node, char *prefix, int is_tail);
void add_symbol(char *name, char *type, int size, int dimension, char *array_spec);
void update_symbol_line(char *name);
void auto_declare_if_needed(char *name);
int lookup_symbol(char *name);
int get_type_size(char *type);
void print_symbol_table();
%}

%union {
    int num;
    float fnum;
    char *str;
    struct ASTNode *node;
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
%type <node> program function_list function param_list param stmt_list stmt
%type <node> declaration assignment if_stmt while_stmt return_stmt
%type <node> expr term factor condition relop

%left PLUS MINUS
%left MUL DIV
%nonassoc LT GT LE GE EQ NE

%%

program:
    function_list { 
        root = $1; 
        $$ = $1; 
    }
    ;

function_list:
    function_list function { 
        if($1 != NULL) {
            ASTNode *temp = $1;
            while(temp->next != NULL) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    | function { $$ = $1; }
    ;

function:
    type ID LPAREN param_list RPAREN LBRACE stmt_list RBRACE {
        add_symbol($2, $1, 0, 1, "-");
        ASTNode *func = create_node("Function", $2, $4, $7);
        $$ = func;
    }
    | type ID LPAREN RPAREN LBRACE stmt_list RBRACE {
        add_symbol($2, $1, 0, 1, "-");
        ASTNode *func = create_node("Function", $2, NULL, $6);
        $$ = func;
    }
    ;

param_list:
    param_list COMMA param {
        $1->next = $3;
        $$ = $1;
    }
    | param { $$ = $1; }
    ;

param:
    type ID { 
        add_symbol($2, $1, get_type_size($1), 1, "-");
        $$ = create_node("Parameter", $2, NULL, NULL);
    }
    ;

type:
    INT { $$ = strdup("int"); }
    | FLOAT { $$ = strdup("float"); }
    | CHAR { $$ = strdup("char"); }
    | DOUBLE { $$ = strdup("double"); }
    | VOID { $$ = strdup("void"); }
    ;

stmt_list:
    stmt_list stmt {
        if($1 == NULL) $$ = $2;
        else {
            ASTNode *temp = $1;
            while(temp->next != NULL) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        }
    }
    | { $$ = NULL; }
    ;

stmt:
    declaration { $$ = $1; }
    | assignment { $$ = $1; }
    | if_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    ;

declaration:
    type ID SEMI { 
        add_symbol($2, $1, get_type_size($1), 1, "-");
        $$ = create_node("Declaration", $2, NULL, NULL);
    }
    | type ID LBRACKET NUM RBRACKET SEMI {
        char dim[20];
        sprintf(dim, "[%d]", $4);
        add_symbol($2, $1, get_type_size($1) * $4, 1, dim);
        $$ = create_node("Array_Declaration", $2, NULL, NULL);
    }
    | type ID LBRACKET NUM RBRACKET LBRACKET NUM RBRACKET SEMI {
        char dim[20];
        sprintf(dim, "[%d][%d]", $4, $7);
        add_symbol($2, $1, get_type_size($1) * $4 * $7, 2, dim);
        $$ = create_node("Array_Declaration", $2, NULL, NULL);
    }
    | type ID ASSIGN expr SEMI {
        add_symbol($2, $1, get_type_size($1), 1, "-");
        ASTNode *decl = create_node("Declaration", $2, NULL, NULL);
        $$ = create_node("=", "", decl, $4);
    }
    ;

assignment:
    ID ASSIGN expr SEMI {
        auto_declare_if_needed($1);
        update_symbol_line($1);
        ASTNode *id_node = create_node("ID", $1, NULL, NULL);
        $$ = create_node("=", "", id_node, $3);
    }
    | ID LBRACKET expr RBRACKET ASSIGN expr SEMI {
        auto_declare_if_needed($1);
        update_symbol_line($1);
        ASTNode *id_node = create_node("ID", $1, NULL, NULL);
        ASTNode *arr = create_node("Array_Access", "", id_node, $3);
        $$ = create_node("=", "", arr, $6);
    }
    ;

if_stmt:
    IF LPAREN condition RPAREN LBRACE stmt_list RBRACE {
        $$ = create_node("if", "", $3, $6);
    }
    | IF LPAREN condition RPAREN LBRACE stmt_list RBRACE ELSE LBRACE stmt_list RBRACE {
        ASTNode *if_part = create_node("if", "", $3, $6);
        ASTNode *else_part = create_node("else", "", NULL, $10);
        if_part->next = else_part;
        $$ = if_part;
    }
    ;

while_stmt:
    WHILE LPAREN condition RPAREN LBRACE stmt_list RBRACE {
        $$ = create_node("while", "", $3, $6);
    }
    ;

return_stmt:
    RETURN expr SEMI {
        $$ = create_node("return", "", $2, NULL);
    }
    | RETURN SEMI {
        $$ = create_node("return", "", NULL, NULL);
    }
    ;

condition:
    expr relop expr {
        $$ = create_node($2->value, "", $1, $3);
    }
    ;

relop:
    LT { $$ = create_node("Relop", "<", NULL, NULL); }
    | GT { $$ = create_node("Relop", ">", NULL, NULL); }
    | LE { $$ = create_node("Relop", "<=", NULL, NULL); }
    | GE { $$ = create_node("Relop", ">=", NULL, NULL); }
    | EQ { $$ = create_node("Relop", "==", NULL, NULL); }
    | NE { $$ = create_node("Relop", "!=", NULL, NULL); }
    ;

expr:
    expr PLUS term {
        $$ = create_node("+", "", $1, $3);
    }
    | expr MINUS term {
        $$ = create_node("-", "", $1, $3);
    }
    | term { $$ = $1; }
    ;

term:
    term MUL factor {
        $$ = create_node("*", "", $1, $3);
    }
    | term DIV factor {
        $$ = create_node("/", "", $1, $3);
    }
    | factor { $$ = $1; }
    ;

factor:
    LPAREN expr RPAREN { $$ = $2; }
    | ID { 
        auto_declare_if_needed($1);
        update_symbol_line($1);
        $$ = create_node("ID", $1, NULL, NULL);
    }
    | NUM { 
        char num_str[20];
        sprintf(num_str, "%d", $1);
        $$ = create_node("NUM", num_str, NULL, NULL);
    }
    | FLOAT_NUM {
        char num_str[20];
        sprintf(num_str, "%.2f", $1);
        $$ = create_node("FLOAT", num_str, NULL, NULL);
    }
    | ID LBRACKET expr RBRACKET {
        auto_declare_if_needed($1);
        update_symbol_line($1);
        ASTNode *id_node = create_node("ID", $1, NULL, NULL);
        $$ = create_node("Array_Access", "", id_node, $3);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}

ASTNode* create_node(char *type, char *value, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    strcpy(node->type, type);
    strcpy(node->value, value);
    node->left = left;
    node->right = right;
    node->next = NULL;
    return node;
}

void print_ast(ASTNode *node, char *prefix, int is_tail) {
    if(node == NULL) return;
    
    printf("%s", prefix);
    printf("%s", is_tail ? "└── " : "├── ");
    
    if(strlen(node->value) > 0) {
        printf("%s: %s\n", node->type, node->value);
    } else {
        printf("%s\n", node->type);
    }
    
    char new_prefix[200];
    strcpy(new_prefix, prefix);
    strcat(new_prefix, is_tail ? "    " : "│   ");
    
    int child_count = 0;
    if(node->left) child_count++;
    if(node->right) child_count++;
    
    if(node->left) {
        print_ast(node->left, new_prefix, (child_count == 1));
        child_count--;
    }
    
    if(node->right) {
        print_ast(node->right, new_prefix, 1);
    }
    
    if(node->next) {
        print_ast(node->next, prefix, 0);
    }
}

int get_type_size(char *type) {
    if(strcmp(type, "int") == 0) return 4;
    if(strcmp(type, "float") == 0) return 4;
    if(strcmp(type, "char") == 0) return 1;
    if(strcmp(type, "double") == 0) return 8;
    return 0;
}

int lookup_symbol(char *name) {
    for(int i = 0; i < symbol_count; i++) {
        if(strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_symbol(char *name, char *type, int size, int dimension, char *array_spec) {
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
    symbol_table[symbol_count].size = size;
    symbol_table[symbol_count].dimension = dimension;
    strcpy(symbol_table[symbol_count].array_spec, array_spec);
    sprintf(symbol_table[symbol_count].lines, "%d", line_num);
    symbol_table[symbol_count].address = address_counter;
    
    address_counter += (size > 0 ? size : 4);
    symbol_count++;
}

void auto_declare_if_needed(char *name) {
    if(lookup_symbol(name) == -1) {
        add_symbol(name, "int", 4, 1, "-");
    }
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
    
    printf("%-15s %-10s %-6s %-12s %-15s %-10s\n", 
           "NAME", "TYPE", "SIZE", "DIMENSION", "LINE", "ADDRESS");
    printf("---------------------------------------------------------------\n");
    
    for(int i = 0; i < symbol_count; i++) {
        char dim_display[50];
        
        if(strcmp(symbol_table[i].array_spec, "-") == 0) {
            sprintf(dim_display, "%d", symbol_table[i].dimension);
        } else {
            sprintf(dim_display, "%d %s", symbol_table[i].dimension, symbol_table[i].array_spec);
        }
        
        printf("%-15s %-10s %-6d %-12s %-15s %-10d\n",
               symbol_table[i].name,
               symbol_table[i].type,
               symbol_table[i].size,
               dim_display,
               symbol_table[i].lines,
               symbol_table[i].address);
    }
    
    printf("---------------------------------------------------------------\n");
    printf("Total Symbols: %d\n", symbol_count);
    printf("===============================================================\n");
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    
    printf("===============================================================\n");
    printf("       TASK 4: PARSER / ABSTRACT SYNTAX TREE\n");
    printf("===============================================================\n\n");
    
    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            printf("Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
        yyin = input_file;
        printf("Input File: %s\n", argv[1]);
    } else {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    yyparse();
    
    print_symbol_table();
    
    printf("\n===============================================================\n");
    printf("                 ABSTRACT SYNTAX TREE\n");
    printf("===============================================================\n\n");
    
    if(root != NULL) {
        print_ast(root, "", 1);
    }
    
    printf("\n===============================================================\n");
    printf("✓ AST generated successfully!\n");
    printf("===============================================================\n");
    
    if (argc > 1) fclose(input_file);
    
    return 0;
}
