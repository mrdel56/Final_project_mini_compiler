%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern FILE *yyin;

int line_num = 1;
int temp_count = 0;
int label_count = 1;

typedef struct {
    char op[20], arg1[50], arg2[50], result[50];
} Quadruple;

Quadruple tac[1000];
int tac_count = 0;

typedef struct {
    int false_pos;
    int end_pos;
    char false_label[20];
    char end_label[20];
} PatchInfo;

PatchInfo stack[100];
int sp = -1;

void yyerror(const char *s);
char* new_temp();
char* new_label();
void gen(char *op, char *arg1, char *arg2, char *result);
void print_tac();
void print_quadruples();
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

%type <str> expr term factor condition relop

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
    type_spec ID LPAREN RPAREN LBRACE stmt_list RBRACE
    | type_spec ID LPAREN param_list RPAREN LBRACE stmt_list RBRACE
    ;

param_list:
    param_list COMMA type_spec ID
    | type_spec ID
    ;

type_spec:
    INT
    | FLOAT
    | CHAR
    | DOUBLE
    | VOID
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
    ;

declaration:
    type_spec ID SEMI
    | type_spec ID LBRACKET NUM RBRACKET SEMI
    | type_spec ID LBRACKET NUM RBRACKET LBRACKET NUM RBRACKET SEMI
    | type_spec ID ASSIGN expr SEMI { gen("=", $4, "", $2); }
    ;

assignment:
    ID ASSIGN expr SEMI { gen("=", $3, "", $1); }
    | ID LBRACKET expr RBRACKET ASSIGN expr SEMI {
        char tmp[100];
        sprintf(tmp, "%s[%s]", $1, $3);
        gen("=", $6, "", tmp);
    }
    ;

if_stmt:
    IF LPAREN condition RPAREN {
        char *Lfalse = new_label();
        gen("ifFalse", $3, "", Lfalse);
        sp++;
        stack[sp].false_pos = tac_count - 1;
        strcpy(stack[sp].false_label, Lfalse);
    } LBRACE stmt_list RBRACE {
        char *Lend = new_label();
        gen("goto", "", "", Lend);
        stack[sp].end_pos = tac_count - 1;
        strcpy(stack[sp].end_label, Lend);
        gen("Label", "", "", stack[sp].false_label);
    } else_part {
        gen("Label", "", "", stack[sp].end_label);
        sp--;
    }
    ;

else_part:
    ELSE LBRACE stmt_list RBRACE
    | /* empty */
    ;

while_stmt:
    WHILE {
        char *Lstart = new_label();
        gen("Label", "", "", Lstart);
        sp++;
        strcpy(stack[sp].false_label, Lstart);
    } LPAREN condition RPAREN {
        char *Lend = new_label();
        gen("ifFalse", $4, "", Lend);
        strcpy(stack[sp].end_label, Lend);
    } LBRACE stmt_list RBRACE {
        gen("goto", "", "", stack[sp].false_label);
        gen("Label", "", "", stack[sp].end_label);
        sp--;
    }
    ;

return_stmt:
    RETURN expr SEMI { gen("return", $2, "", ""); }
    | RETURN SEMI { gen("return", "", "", ""); }
    ;

condition:
    expr relop expr {
        char *tmp = new_temp();
        gen($2, $1, $3, tmp);
        $$ = tmp;
    }
    ;

relop:
    LT { $$ = strdup("<"); }
    | GT { $$ = strdup(">"); }
    | LE { $$ = strdup("<="); }
    | GE { $$ = strdup(">="); }
    | EQ { $$ = strdup("=="); }
    | NE { $$ = strdup("!="); }
    ;

expr:
    expr PLUS term {
        char *tmp = new_temp();
        gen("+", $1, $3, tmp);
        $$ = tmp;
    }
    | expr MINUS term {
        char *tmp = new_temp();
        gen("-", $1, $3, tmp);
        $$ = tmp;
    }
    | term { $$ = $1; }
    ;

term:
    term MUL factor {
        char *tmp = new_temp();
        gen("*", $1, $3, tmp);
        $$ = tmp;
    }
    | term DIV factor {
        char *tmp = new_temp();
        gen("/", $1, $3, tmp);
        $$ = tmp;
    }
    | factor { $$ = $1; }
    ;

factor:
    LPAREN expr RPAREN { $$ = $2; }
    | ID { $$ = $1; }
    | NUM {
        char *buf = (char*)malloc(16);
        sprintf(buf, "%d", $1);
        $$ = buf;
    }
    | FLOAT_NUM {
        char *buf = (char*)malloc(16);
        sprintf(buf, "%.2f", $1);
        $$ = buf;
    }
    | ID LBRACKET expr RBRACKET {
        char *buf = (char*)malloc(64);
        sprintf(buf, "%s[%s]", $1, $3);
        $$ = buf;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}

char* new_temp() {
    char *t = (char*)malloc(10);
    sprintf(t, "t%d", temp_count++);
    return t;
}

char* new_label() {
    char *l = (char*)malloc(10);
    sprintf(l, "L%d", label_count++);
    return l;
}

void gen(char *op, char *arg1, char *arg2, char *result) {
    strcpy(tac[tac_count].op, op);
    strcpy(tac[tac_count].arg1, arg1 ? arg1 : "");
    strcpy(tac[tac_count].arg2, arg2 ? arg2 : "");
    strcpy(tac[tac_count].result, result ? result : "");
    tac_count++;
}

void print_tac() {
    printf("\n===============================================================\n");
    printf("                    OUTPUT OF TAC\n");
    printf("===============================================================\n\n");
    for(int i = 0; i < tac_count; i++) {
        if (!strcmp(tac[i].op, "="))
            printf("%s = %s\n", tac[i].result, tac[i].arg1);
        else if (!strcmp(tac[i].op, "Label"))
            printf("%s:\n", tac[i].result);
        else if (!strcmp(tac[i].op, "goto"))
            printf("goto %s\n", tac[i].result);
        else if (!strcmp(tac[i].op, "ifFalse"))
            printf("ifFalse %s goto %s\n", tac[i].arg1, tac[i].result);
        else if (!strcmp(tac[i].op, "return")) {
            if (strlen(tac[i].arg1) > 0)
                printf("return %s\n", tac[i].arg1);
            else
                printf("return\n");
        } else
            printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
    }
    printf("\n===============================================================\n");
    printf("✓ Intermediate Code generated successfully!\n");
    printf("===============================================================\n");
}

void print_quadruples() {
    printf("\n===============================================================\n");
    printf("                    QUADRUPLE FORMAT\n");
    printf("===============================================================\n\n");
    printf("%-10s %-20s %-20s %-20s\n", "Op", "Arg1", "Arg2", "Res");
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < tac_count; i++)
        printf("%-10s %-20s %-20s %-20s\n",
               tac[i].op, tac[i].arg1, tac[i].arg2, tac[i].result);
    printf("---------------------------------------------------------------\n");
    printf("Total Instructions: %d\n", tac_count);
    printf("===============================================================\n");
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    printf("===============================================================\n");
    printf("      TASK 5: INTERMEDIATE CODE GENERATION (TAC)\n");
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
    print_tac();
    print_quadruples();
    if (argc > 1) fclose(input_file);
    return 0;
}
