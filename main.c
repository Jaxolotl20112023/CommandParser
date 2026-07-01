#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashMap.h"

char* get_line_info(char* ptr, int offset, int override) {

	int len = strlen(ptr);
	int spaces = 0; 

	char* new_ptr = calloc(len,sizeof(char)); 


	for (int i=offset; i<len; i++) {
	
		if (ptr[i] == ' ' && override == 0) { 
		       break;
	       	}

		
		new_ptr[i-offset] = ptr[i]; 	
	}

	if (offset >= len) return NULL; 	


	return new_ptr;
}

void compile_data(lines_t* lines, int num_lines) {
	
//	printf("command len: %d", COMMAND_LEN);
	for (int j=0; j<num_lines; j++) {
	//	printf("num lines: %d\n", num_lines);


		for (int i=0; i<COMMAND_LEN; i++) {
		//	printf("key: %s v. command: %s\n", commands[i].key,lines[j].line_command);
			if (strcmp(commands[i].key,lines[j].line_command) == 0)  {
		//		printf("match\n");
				commands[i].item(j, lines);
				break;
			}
		}

	}
}

int main() {

	lines_t* lines = calloc(50,sizeof(lines_t)); 
	int i=0; 

	//commands[0].item(2,"hi!","you pickle!!\n");

	while (1) {
		char buffer[50];
		char* ptr; 

		fgets(buffer, 50, stdin); 

		ptr = buffer; 

		lines[i].line_num = i; 

		lines[i].line_command = get_line_info(ptr,0,0); 
		int commandLen = strlen(lines[i].line_command)+1; 

		if (strcmp(lines[i].line_command,"end\n") == 0){
			break;
		}

		lines[i].line_data = get_line_info(ptr,commandLen,1);

		i++; 
	}


	compile_data(lines,i);
	

	return 0;

}



