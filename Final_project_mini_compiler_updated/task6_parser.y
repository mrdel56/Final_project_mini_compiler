%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int yylex();
extern FILE *yyin;

int line_num = 1;
int temp_count = 0;
int label_count = 1;

typedef struct {
    char op[20], arg1[50], arg2[50], result[50];
    int is_dead;
} Quadruple;

Quadruple tac[1000];
int tac_count = 0;

typedef struct {
    char var[50];
    int value;
    int is_const;
    int is_used;
} VarInfo;

VarInfo var_table[200];
int var_count = 0;

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
void print_tac(const char *title);
void print_quadruples();

// Optimization functions
void constant_propagation();
void constant_folding();
void enhanced_constant_folding();
void dead_code_elimination();
void eliminate_unreachable_code();
int find_var(const char *name);
void update_var(const char *name, int value, int is_const);
int is_constant(const char *str);
int evaluate_expr(const char *op, int val1, int val2);
void mark_used_vars();
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

program: function_list ;
function_list: function_list function | function ;
function: type_spec ID LPAREN RPAREN LBRACE stmt_list RBRACE | type_spec ID LPAREN param_list RPAREN LBRACE stmt_list RBRACE ;
param_list: param_list COMMA type_spec ID | type_spec ID ;
type_spec: INT | FLOAT | CHAR | DOUBLE | VOID ;
stmt_list: stmt_list stmt | /* empty */ ;
stmt: declaration | assignment | if_stmt | while_stmt | return_stmt ;

declaration:
    type_spec ID SEMI
    | type_spec ID LBRACKET NUM RBRACKET SEMI
    | type_spec ID LBRACKET NUM RBRACKET LBRACKET NUM RBRACKET SEMI
    | type_spec ID ASSIGN expr SEMI { gen("=", $4, "", $2); }
    ;

assignment:
    ID ASSIGN expr SEMI { gen("=", $3, "", $1); }
    | ID LBRACKET expr RBRACKET ASSIGN expr SEMI {
        char tmp[100]; sprintf(tmp, "%s[%s]", $1, $3);
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

else_part: ELSE LBRACE stmt_list RBRACE | /* empty */ ;

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

return_stmt: RETURN expr SEMI { gen("return", $2, "", ""); } | RETURN SEMI { gen("return", "", "", ""); } ;

condition: expr relop expr { char *tmp = new_temp(); gen($2, $1, $3, tmp); $$ = tmp; } ;

relop:
    LT { $$ = strdup("<"); } | GT { $$ = strdup(">"); }
    | LE { $$ = strdup("<="); } | GE { $$ = strdup(">="); }
    | EQ { $$ = strdup("=="); } | NE { $$ = strdup("!="); } ;

expr:
    expr PLUS term { char *tmp = new_temp(); gen("+", $1, $3, tmp); $$ = tmp; }
    | expr MINUS term { char *tmp = new_temp(); gen("-", $1, $3, tmp); $$ = tmp; }
    | term { $$ = $1; }
    ;

term:
    term MUL factor { char *tmp = new_temp(); gen("*", $1, $3, tmp); $$ = tmp; }
    | term DIV factor { char *tmp = new_temp(); gen("/", $1, $3, tmp); $$ = tmp; }
    | factor { $$ = $1; }
    ;

factor:
    LPAREN expr RPAREN { $$ = $2; }
    | ID { $$ = $1; }
    | NUM { char *buf = (char*)malloc(16); sprintf(buf, "%d", $1); $$ = buf; }
    | FLOAT_NUM { char *buf = (char*)malloc(16); sprintf(buf, "%.2f", $1); $$ = buf; }
    | ID LBRACKET expr RBRACKET { char *buf = (char*)malloc(64); sprintf(buf, "%s[%s]", $1, $3); $$ = buf; }
    ;

%%

void yyerror(const char *s) { fprintf(stderr, "Error at line %d: %s\n", line_num, s); }

char* new_temp() { char *t = (char*)malloc(10); sprintf(t, "t%d", temp_count++); return t; }
char* new_label() { char *l = (char*)malloc(10); sprintf(l, "L%d", label_count++); return l; }

void gen(char *op, char *arg1, char *arg2, char *result) {
    strcpy(tac[tac_count].op, op);
    strcpy(tac[tac_count].arg1, arg1 ? arg1 : "");
    strcpy(tac[tac_count].arg2, arg2 ? arg2 : "");
    strcpy(tac[tac_count].result, result ? result : "");
    tac[tac_count].is_dead = 0;
    tac_count++;
}

int find_var(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].var, name) == 0) return i;
    }
    return -1;
}

void update_var(const char *name, int value, int is_const) {
    int idx = find_var(name);
    if (idx == -1) {
        strcpy(var_table[var_count].var, name);
        var_table[var_count].value = value;
        var_table[var_count].is_const = is_const;
        var_table[var_count].is_used = 0;
        var_count++;
    } else {
        var_table[idx].value = value;
        var_table[idx].is_const = is_const;
    }
}

int is_constant(const char *str) {
    if (!str || strlen(str) == 0) return 0;
    int i = 0;
    if (str[0] == '-') i = 1;
    for (; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int evaluate_expr(const char *op, int val1, int val2) {
    if (strcmp(op, "+") == 0) return val1 + val2;
    if (strcmp(op, "-") == 0) return val1 - val2;
    if (strcmp(op, "*") == 0) return val1 * val2;
    if (strcmp(op, "/") == 0) return val2 != 0 ? val1 / val2 : 0;
    if (strcmp(op, ">=") == 0) return val1 >= val2;
    if (strcmp(op, "<=") == 0) return val1 <= val2;
    if (strcmp(op, ">") == 0) return val1 > val2;
    if (strcmp(op, "<") == 0) return val1 < val2;
    if (strcmp(op, "==") == 0) return val1 == val2;
    if (strcmp(op, "!=") == 0) return val1 != val2;
    return 0;
}

void constant_propagation() {
    for (int i = 0; i < tac_count; i++) {
        if (strcmp(tac[i].op, "Label") == 0 || strcmp(tac[i].op, "goto") == 0 || strcmp(tac[i].op, "ifFalse") == 0) continue;

        if (strcmp(tac[i].op, "=") == 0) {
            if (is_constant(tac[i].arg1)) {
                update_var(tac[i].result, atoi(tac[i].arg1), 1);
            } else {
                int idx = find_var(tac[i].arg1);
                if (idx != -1 && var_table[idx].is_const) {
                    sprintf(tac[i].arg1, "%d", var_table[idx].value);
                    update_var(tac[i].result, var_table[idx].value, 1);
                } else {
                    update_var(tac[i].result, 0, 0);
                }
            }
        } else if (strlen(tac[i].arg2) > 0) {
            int idx1 = find_var(tac[i].arg1);
            if (idx1 != -1 && var_table[idx1].is_const) {
                sprintf(tac[i].arg1, "%d", var_table[idx1].value);
            }
            int idx2 = find_var(tac[i].arg2);
            if (idx2 != -1 && var_table[idx2].is_const) {
                sprintf(tac[i].arg2, "%d", var_table[idx2].value);
            }
        }
    }
}

void constant_folding() {
    for (int i = 0; i < tac_count; i++) {
        if (strlen(tac[i].arg2) > 0 && strcmp(tac[i].op, "Label") != 0 && strcmp(tac[i].op, "goto") != 0 && strcmp(tac[i].op, "ifFalse") != 0) {
            if (is_constant(tac[i].arg1) && is_constant(tac[i].arg2)) {
                int val1 = atoi(tac[i].arg1);
                int val2 = atoi(tac[i].arg2);
                int result = evaluate_expr(tac[i].op, val1, val2);
                strcpy(tac[i].op, "=");
                sprintf(tac[i].arg1, "%d", result);
                tac[i].arg2[0] = '\0';
                update_var(tac[i].result, result, 1);
            }
        }
    }
}

void enhanced_constant_folding() {
    int changed = 1;
    int iterations = 0;
    while (changed && iterations < 5) {
        changed = 0;
        iterations++;
        
        // First propagate all known constants
        for (int i = 0; i < tac_count; i++) {
            if (strcmp(tac[i].op, "=") == 0 && is_constant(tac[i].arg1)) {
                update_var(tac[i].result, atoi(tac[i].arg1), 1);
            }
        }
        
        // Then try to fold expressions
        for (int i = 0; i < tac_count; i++) {
            if (strlen(tac[i].arg2) > 0) {
                int idx1 = find_var(tac[i].arg1);
                if (idx1 != -1 && var_table[idx1].is_const && !is_constant(tac[i].arg1)) {
                    sprintf(tac[i].arg1, "%d", var_table[idx1].value);
                    changed = 1;
                }
                int idx2 = find_var(tac[i].arg2);
                if (idx2 != -1 && var_table[idx2].is_const && !is_constant(tac[i].arg2)) {
                    sprintf(tac[i].arg2, "%d", var_table[idx2].value);
                    changed = 1;
                }
                if (is_constant(tac[i].arg1) && is_constant(tac[i].arg2)) {
                    int result = evaluate_expr(tac[i].op, atoi(tac[i].arg1), atoi(tac[i].arg2));
                    strcpy(tac[i].op, "=");
                    sprintf(tac[i].arg1, "%d", result);
                    tac[i].arg2[0] = '\0';
                    update_var(tac[i].result, result, 1);
                    changed = 1;
                }
            }
        }
    }
}

void eliminate_unreachable_code() {
    for (int i = 0; i < tac_count; i++) {
        // Look for ifFalse with constant condition
        if (strcmp(tac[i].op, "ifFalse") == 0) {
            // Check if condition is a constant
            char *cond_var = tac[i].arg1;
            int is_const = 0;
            int cond_value = 0;
            
            // Check if it's a number
            if (is_constant(cond_var)) {
                is_const = 1;
                cond_value = atoi(cond_var);
            } else {
                // Check if it's a known constant variable
                int idx = find_var(cond_var);
                if (idx != -1 && var_table[idx].is_const) {
                    is_const = 1;
                    cond_value = var_table[idx].value;
                }
            }
            
            if (is_const) {
                // If condition is true (non-zero), jump never happens
                // So the target (else branch) is unreachable
                if (cond_value != 0) {
                    // Mark ifFalse as dead
                    tac[i].is_dead = 1;
                    
                    // Get the label of the else branch
                    char *dead_label = tac[i].result;
                    int marking = 0;
                    
                    // Find and mark the entire else branch as dead
                    for (int j = i + 1; j < tac_count; j++) {
                        if (strcmp(tac[j].op, "Label") == 0) {
                            if (strcmp(tac[j].result, dead_label) == 0) {
                                // Start of else branch
                                marking = 1;
                                tac[j].is_dead = 1;
                            } else if (marking) {
                                // Hit another label (end of else) - stop
                                break;
                            }
                        } else if (marking) {
                            // Inside else branch - mark as dead
                            tac[j].is_dead = 1;
                        }
                    }
                    
                    // Also mark the goto at end of then-branch as dead if it's redundant
                    for (int j = i + 1; j < tac_count; j++) {
                        if (strcmp(tac[j].op, "goto") == 0) {
                            char *goto_target = tac[j].result;
                            // Check if next non-dead instruction is this label
                            for (int k = j + 1; k < tac_count; k++) {
                                if (!tac[k].is_dead) {
                                    if (strcmp(tac[k].op, "Label") == 0 && 
                                        strcmp(tac[k].result, goto_target) == 0) {
                                        tac[j].is_dead = 1;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        if (strcmp(tac[j].op, "Label") == 0 && 
                            strcmp(tac[j].result, dead_label) == 0) {
                            break;
                        }
                    }
                }
            }
        }
    }
}


void mark_used_vars() {
    for (int i = 0; i < tac_count; i++) {
        if (tac[i].is_dead) continue;
        if (strcmp(tac[i].op, "ifFalse") == 0 || strcmp(tac[i].op, "return") == 0) {
            int idx = find_var(tac[i].arg1);
            if (idx != -1) var_table[idx].is_used = 1;
        }
        if (strlen(tac[i].arg1) > 0 && !is_constant(tac[i].arg1)) {
            int idx = find_var(tac[i].arg1);
            if (idx != -1) var_table[idx].is_used = 1;
        }
        if (strlen(tac[i].arg2) > 0 && !is_constant(tac[i].arg2)) {
            int idx = find_var(tac[i].arg2);
            if (idx != -1) var_table[idx].is_used = 1;
        }
    }
}

void dead_code_elimination() {
    mark_used_vars();
    for (int i = 0; i < tac_count; i++) {
        if (tac[i].is_dead) continue;
        if ((strcmp(tac[i].op, "=") == 0 || strlen(tac[i].result) > 0) && tac[i].result[0] == 't') {
            int idx = find_var(tac[i].result);
            if (idx != -1 && !var_table[idx].is_used) {
                tac[i].is_dead = 1;
            }
        }
    }
}

void print_tac(const char *title) {
    printf("\n===============================================================\n");
    printf("           %s\n", title);
    printf("===============================================================\n\n");
    
    for (int i = 0; i < tac_count; i++) {
        // IMPORTANT: Skip dead code
        if (tac[i].is_dead) continue;
        
        if (strlen(tac[i].op) == 0) continue;
        
        if (strcmp(tac[i].op, "=") == 0)
            printf("%s = %s\n", tac[i].result, tac[i].arg1);
        else if (strcmp(tac[i].op, "Label") == 0)
            printf("%s:\n", tac[i].result);
        else if (strcmp(tac[i].op, "goto") == 0)
            printf("goto %s\n", tac[i].result);
        else if (strcmp(tac[i].op, "ifFalse") == 0)
            printf("ifFalse %s goto %s\n", tac[i].arg1, tac[i].result);
        else if (strcmp(tac[i].op, "return") == 0) {
            if (strlen(tac[i].arg1) > 0) printf("return %s\n", tac[i].arg1);
            else printf("return\n");
        } else
            printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
    }
}


void print_quadruples() {
    printf("\n===============================================================\n");
    printf("                    QUADRUPLE FORMAT\n");
    printf("===============================================================\n\n");
    printf("%-10s %-20s %-20s %-20s\n", "Op", "Arg1", "Arg2", "Res");
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < tac_count; i++) {
        if (!tac[i].is_dead && strlen(tac[i].op) > 0) {
            printf("%-10s %-20s %-20s %-20s\n", tac[i].op, tac[i].arg1, tac[i].arg2, tac[i].result);
        }
    }
    printf("---------------------------------------------------------------\n");
    printf("===============================================================\n");
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    
    printf("===============================================================\n");
    printf("   TASK 6: INTERMEDIATE CODE GENERATION + OPTIMIZATION\n");
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
    print_tac("INPUT BEFORE OPTIMIZATION");
    print_quadruples();
    
    constant_propagation();
    print_tac("AFTER CONSTANT PROPAGATION");
    
    constant_folding();
    print_tac("AFTER CONSTANT FOLDING");
    
    enhanced_constant_folding();
    print_tac("AFTER ENHANCED CONSTANT FOLDING");
    
    eliminate_unreachable_code();
    print_tac("AFTER UNREACHABLE CODE ELIMINATION");
    
    dead_code_elimination();
    print_tac("AFTER DEAD CODE ELIMINATION (FINAL)");
    
    if (argc > 1) fclose(input_file);
    return 0;
}
