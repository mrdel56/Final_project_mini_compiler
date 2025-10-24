%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;
int address_counter = 1000;

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

char current_type[20] = "";
int in_declaration = 0;
int after_equal = 0;
char last_var[50] = "";

void add_symbol(char *name, char *type, int size, int dimension, char *array_spec);
void update_symbol_line(char *name, int line);
int lookup_symbol(char *name);
void print_symbol_table();
int get_type_size(char *type);
int count_dimensions(char *array_spec);
%}

%option noyywrap

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT         {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+

%%

[ \t]+                  { /* Skip whitespace */ }
\n                      { line_num++; }

"//".*                  { /* Single-line comment */ }
"/*"                    { 
                          int c1 = 0, c2 = input();
                          while(c2 != EOF && !(c1 == '*' && c2 == '/')) {
                              if(c2 == '\n') line_num++;
                              c1 = c2;
                              c2 = input();
                          }
                        }

"int"                   { strcpy(current_type, "int"); in_declaration = 1; }
"float"                 { strcpy(current_type, "float"); in_declaration = 1; }
"char"                  { strcpy(current_type, "char"); in_declaration = 1; }
"double"                { strcpy(current_type, "double"); in_declaration = 1; }
"void"                  { strcpy(current_type, "void"); in_declaration = 1; }

"if"|"else"|"while"|"for" { in_declaration = 0; }
"return"                { in_declaration = 0; }

{ID}"("                 { 
                          if(strlen(current_type) > 0) {
                              char func_name[50];
                              strncpy(func_name, yytext, strlen(yytext)-1);
                              func_name[strlen(yytext)-1] = '\0';
                              
                              if(lookup_symbol(func_name) == -1) {
                                  add_symbol(func_name, current_type, 0, 1, "-");
                              }
                          }
                          in_declaration = 1;
                        }

{ID}("["[0-9]+"]")+     {
                          if(in_declaration && strlen(current_type) > 0) {
                              char name[50], array_spec[20];
                              int i = 0, j = 0;
                              
                              while(yytext[i] != '[') {
                                  name[i] = yytext[i];
                                  i++;
                              }
                              name[i] = '\0';
                              
                              while(yytext[i] != '\0') {
                                  array_spec[j++] = yytext[i++];
                              }
                              array_spec[j] = '\0';
                              
                              if(lookup_symbol(name) == -1) {
                                  int base_size = get_type_size(current_type);
                                  int total_elements = 1;
                                  int dim_count = count_dimensions(array_spec);
                                  
                                  char *ptr = array_spec;
                                  while(*ptr) {
                                      if(*ptr == '[') {
                                          total_elements *= atoi(ptr + 1);
                                      }
                                      ptr++;
                                  }
                                  
                                  add_symbol(name, current_type, base_size * total_elements, dim_count, array_spec);
                              } else {
                                  update_symbol_line(name, line_num);
                              }
                          } else {
                              char name[50];
                              int i = 0;
                              while(yytext[i] != '[') {
                                  name[i] = yytext[i];
                                  i++;
                              }
                              name[i] = '\0';
                              update_symbol_line(name, line_num);
                          }
                        }

{ID}                    { 
                          if(in_declaration && strlen(current_type) > 0) {
                              if(lookup_symbol(yytext) == -1) {
                                  int size = get_type_size(current_type);
                                  add_symbol(yytext, current_type, size, 1, "-");
                                  strcpy(last_var, yytext);
                              } else {
                                  update_symbol_line(yytext, line_num);
                              }
                          } else {
                              update_symbol_line(yytext, line_num);
                              strcpy(last_var, yytext);
                          }
                        }

"="                     { after_equal = 1; }

{FLOAT}                 {
                          if(after_equal && strlen(last_var) > 0) {
                              int idx = lookup_symbol(last_var);
                              if(idx != -1 && strcmp(symbol_table[idx].array_spec, "-") == 0) {
                                  strcpy(symbol_table[idx].type, "float");
                                  symbol_table[idx].size = 4;
                              }
                          }
                        }

{INT}                   { /* Integer literal */ }

";"                     { 
                          in_declaration = 0; 
                          strcpy(current_type, "");
                          after_equal = 0;
                          strcpy(last_var, "");
                        }

"{"                     { in_declaration = 0; }
"}"                     { in_declaration = 0; strcpy(current_type, ""); }
")"                     { /* Closing parenthesis */ }
","                     { /* Comma */ }

"+"|"-"|"*"|"/"|"%"     { after_equal = 0; }
"<"|">"|"<="|">="|"=="|"!=" { /* Relational */ }
"&&"|"||"|"!"           { /* Logical */ }

.                       { /* Ignore */ }

%%

int get_type_size(char *type) {
    if(strcmp(type, "int") == 0) return 4;
    if(strcmp(type, "float") == 0) return 4;
    if(strcmp(type, "char") == 0) return 1;
    if(strcmp(type, "double") == 0) return 8;
    if(strcmp(type, "void") == 0) return 0;
    return 4;
}

int count_dimensions(char *array_spec) {
    int count = 0;
    char *ptr = array_spec;
    while(*ptr) {
        if(*ptr == '[') count++;
        ptr++;
    }
    return count;
}

void add_symbol(char *name, char *type, int size, int dimension, char *array_spec) {
    if(lookup_symbol(name) != -1) {
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

void update_symbol_line(char *name, int line) {
    int idx = lookup_symbol(name);
    if(idx != -1) {
        char temp[200];
        strcpy(temp, symbol_table[idx].lines);
        
        char line_str[10];
        sprintf(line_str, "%d", line);
        if(strstr(temp, line_str) == NULL) {
            strcat(symbol_table[idx].lines, ", ");
            strcat(symbol_table[idx].lines, line_str);
        }
    }
}

int lookup_symbol(char *name) {
    for(int i = 0; i < symbol_count; i++) {
        if(strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
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
    printf("            TASK 2: SYMBOL TABLE CREATION\n");
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
    
    printf("Analyzing source code for symbol table generation...\n");
    
    yylex();
    
    print_symbol_table();
    
    printf("\n✓ Symbol Table generated successfully!\n");
    printf("===============================================================\n");
    
    if (argc > 1) fclose(input_file);
    
    return 0;
}
