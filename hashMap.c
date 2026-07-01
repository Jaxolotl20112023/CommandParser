#pragma once 
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union VarType {

	int intvar;
	float floatvar;
	char charvar;
	char *strvar; 
} var_type; 

typedef enum Types {

	INTEGER,
	FLOAT,
	CHAR,
	STRING
} Types;

typedef struct Type {

	Types kind; 
	var_type var; 

} type_t; 

typedef struct Line {
	
	int line_num; 
	char* line_command; 
	char* line_data;
	type_t output; 

} lines_t; 


typedef struct Command {

	void* (*func)(int n,lines_t* lines); 

} command_t; 

void print(int n,lines_t* lines, ...);
void add(int n,lines_t* lines, ...);
void sub(int n,lines_t* lines, ...);
void mul(int n,lines_t* lines, ...);
void divide(int n,lines_t* lines, ...);

typedef struct HashMap {

	char* key; 
	void (*item)(int n,lines_t* lines, ...);

} hash_map_t;

extern hash_map_t commands[];
extern int COMMAND_LEN;


