#include "hashMap.h"

char* get_subdata(int n, lines_t* lines, int offset) {
	char* temp = calloc(20,sizeof(char));


	for (int i=offset; i<strlen(lines[n].line_data); i++) {

		if (lines[n].line_data[i] == ',' || lines[n].line_data[i] == '\n') {
			break; 
		}

//		printf("line_data char at %d: %c\n",i,lines[n].line_data[i]);
		
		temp[i-offset] = lines[n].line_data[i];
	
	}
	return temp; 
}

int get_char_index(lines_t lines, char item) {

	for (int i=0; i<strlen(lines.line_data); i++) {

		if (lines.line_data[i] == item) {
			return i; 
		}
	}
	
	return -1; 

}

void print(int n, lines_t* lines, ...) {

//	char* output = lines[n].line_data; 
	int val = 0; 
	

	if (get_char_index(lines[n], '<') != -1) {
	      // printf("Print line!\n"); 
	      // printf("Index of <: %d\n", get_char_index(lines[n],'<')); 

	       char* index = calloc(20,sizeof(char)); 
	       for (int i=0; i<get_char_index(lines[n], '<'); i++) {
		       index[i] += lines[n].line_data[i]; 
	       } 

	     //  printf("Index value: %d\n", atoi(index));
	      	
	       val = atoi(index); 
       
	       switch (lines[val].output.kind) {
		case INTEGER:
	       		printf("%d\n",lines[val].output.var.intvar); 
			break; 
		case FLOAT: 
			printf("%f\n",lines[val].output.var.floatvar); 
			break;
		case CHAR:
			printf("%c\n",lines[val].output.var.charvar);
		        break;	
		case STRING:
			printf("%s\n",lines[val].output.var.strvar); 
			break; 
		}

	} else {
		printf("%s",lines[n].line_data); 


	}




}

void add(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0; 

	s_num1 = get_subdata(n,lines, 0); 
	s_num2 = get_subdata(n,lines,strlen(s_num1)+1); 

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

//	printf("num1: %d, num2: %d\n", num1,num2);

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1+num2; 

//	printf("sum: %d\n",lines[n].output.var.intvar); 

	free(s_num1); 
	free(s_num2);

}

void sub(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0; 

	s_num1 = get_subdata(n,lines, 0); 
	s_num2 = get_subdata(n,lines,strlen(s_num1)+1); 

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

//	printf("num1: %d, num2: %d\n", num1,num2);

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1-num2; 

//	printf("diff: %d\n",lines[n].output.var.intvar); 

	free(s_num1); 
	free(s_num2);

}

void mul(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0; 

	s_num1 = get_subdata(n,lines, 0); 
	s_num2 = get_subdata(n,lines,strlen(s_num1)+1); 

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

//	printf("num1: %d, num2: %d\n", num1,num2);

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1*num2; 

//	printf("diff: %d\n",lines[n].output.var.intvar); 

	free(s_num1); 
	free(s_num2);

}

void divide(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0; 

	s_num1 = get_subdata(n,lines, 0); 
	s_num2 = get_subdata(n,lines,strlen(s_num1)+1); 

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

//	printf("num1: %d, num2: %d\n", num1,num2);

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1/num2; 

//	printf("diff: %d\n",lines[n].output.var.intvar); 

	free(s_num1); 
	free(s_num2);

}


hash_map_t commands[] = {
	{"print", print},
	{"add", add}, 
	{"sub",sub},
	{"mul",mul},
	{"div",divide}
};

int COMMAND_LEN = 5; 
