#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashMap.h"

compiler_t* compile_manage; 

char* get_line_info(char* ptr, int offset, int override) {

	int len = strlen(ptr);
	int spaces = 0; 

	char* new_ptr = calloc(len,sizeof(char)); 


	for (int i=offset; i<len; i++) {

	//	printf("%c",ptr[i]);
	
		if (ptr[i] == ' ' && override == 0) { 
		       break;
	       	}

		
		new_ptr[i-offset] = ptr[i]; 	
	}

	if (offset >= len) return NULL; 	


	return new_ptr;
}
				



void compile_data(lines_t* lines, int max) {
	
//	compiler_t* compile_manage = malloc(sizeof(compiler_t)); 
//	compile_manage->curr_line = 0; 
//	compile_manage->curr_cmd = 0;
//     	compile_manage->total_lines = max;
	
	while (compile_manage->curr_line < compile_manage->total_lines) {

		while (compile_manage->curr_cmd < 11) {

	//		printf("cmd: %s vs input: %s\n", commands[compile_manage->curr_cmd].key, lines[compile_manage->curr_line].line_command);
	//		put check_var function in here to check for every variable

			if (strcmp(commands[compile_manage->curr_cmd].key,lines[compile_manage->curr_line].line_command) == 0)  {
	//			printf("match\n");
				commands[compile_manage->curr_cmd].item(compile_manage->curr_line, lines, compile_manage);
				break;
			}
			compile_manage->curr_cmd++; 
		}
		compile_manage->curr_line++; 
		compile_manage->curr_cmd = 0; 
	}


}

int main(int argc, char *argv[]) {

	FILE* fptr; 

	fptr = fopen(argv[1],"r"); 

	if (fptr == NULL) {
		printf("FILE NOT OPENED"); 
	        return 1;
	}	

	lines_t* lines = calloc(50,sizeof(lines_t)); 

	compile_manage = malloc(sizeof(compiler_t));
	compile_manage->curr_line = 0; 
	compile_manage->curr_cmd = 0;

	int i=0; 

	//commands[0].item(2,"hi!","you pickle!!\n");

	while (1) {
		char buffer[50];
		char* ptr; 

		fgets(buffer, 50, fptr); 

		ptr = buffer; 

	//	printf("Line: %s\n", ptr); 

		lines[i].line_num = i; 

		lines[i].line_command = get_line_info(ptr,0,0); 
		int commandLen = strlen(lines[i].line_command)+1;
	        
	//	printf("Line command: %sf v. ptr: %sf\n", lines[i].line_command, ptr);

		if (lines[i].line_command[0] == ' ' || lines[i].line_command[0] == '\n') continue;	


		if (strcmp(lines[i].line_command,"end") == 0){
			break;
		}

		lines[i].line_data = get_line_info(ptr,commandLen,1);

		i++; 

	}

	compile_manage->total_lines = i;

	compile_data(lines,i);

	

	return 0;

}



