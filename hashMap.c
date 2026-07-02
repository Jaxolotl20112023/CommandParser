#include "hashMap.h"

char* get_subdata(lines_t lines, int offset) {
	char* temp = calloc(20,sizeof(char));


	for (int i=offset; i<strlen(lines.line_data); i++) {

		if (lines.line_data[i] == ',' || lines.line_data[i] == '\n') {
			break; 
		}

//		printf("line_data char at %d: %c\n",i,lines[n].line_data[i]);
		
		temp[i-offset] = lines.line_data[i];
	
	}
	return temp; 
}

int get_char_index(char* str, char item) {

	for (int i=0; i<strlen(str); i++) {

		if (str[i] == item) {
			return i; 
		}
	}
	
	return -1; 

}

void print(int n, lines_t* lines, ...) {

//	char* output = lines[n].line_data; 
	int val = 0; 
	

	if (get_char_index(lines[n].line_data, '@') != -1) {
	      // printf("Print line!\n"); 
	      // printf("Index of <: %d\n", get_char_index(lines[n],'<')); 

	       char* index = calloc(20,sizeof(char)); 
	       for (int i=0; i<get_char_index(lines[n].line_data, '@'); i++) {
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

	s_num1 = get_subdata(lines[n], 0); 
	s_num2 = get_subdata(lines[n],strlen(s_num1)+1); 

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

	s_num1 = get_subdata(lines[n], 0); 
	s_num2 = get_subdata(lines[n],strlen(s_num1)+1); 


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

	s_num1 = get_subdata(lines[n], 0); 
	s_num2 = get_subdata(lines[n],strlen(s_num1)+1);

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

	s_num1 = get_subdata(lines[n], 0); 
	s_num2 = get_subdata(lines[n],strlen(s_num1)+1);

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

//	printf("num1: %d, num2: %d\n", num1,num2);

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1/num2; 

//	printf("diff: %d\n",lines[n].output.var.intvar); 

	free(s_num1); 
	free(s_num2);

}


void go_to(int n, lines_t* lines, ...) {

	unsigned max = 1; 
	va_list args; 
	va_start(args,lines); 
        
	compiler_t* compiler = va_arg(args,compiler_t*); 

	int target = (atoi(lines[n].line_data))-1;

	if (target > compiler->total_lines || target < 0) return; 

	compiler->curr_line = target; 
	compiler->curr_cmd = 0;
//   	printf("compiler curr_ljne: %d\n", compiler->curr_line);	

	va_end(args); 
}

void less_than(int n, lines_t* lines, ...) {


	char* s_num1 = calloc(5,sizeof(char)); 
	char* s_num2 = calloc(5,sizeof(char));


	s_num1 = get_subdata(lines[n],0); 
	s_num2 = get_subdata(lines[n],strlen(s_num1)+1);

	int num1 = atoi(s_num1); 
	int num2 = atoi(s_num2);


	lines[n].output.kind = INTEGER; 

	if (num1 < num2) {
		lines[n].output.var.intvar = 1; 
	} else {
	       	lines[n].output.var.intvar = 0; 
	}

	free(s_num1); 
	free(s_num2); 

}

void greater_than(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(5,sizeof(char)); 
	char* s_num2 = calloc(5,sizeof(char)); 

	s_num1 = get_subdata(lines[n],0); 
	s_num2 = get_subdata(lines[n],strlen(s_num1)+1);

	int num1 = atoi(s_num1); 
	int num2 = atoi(s_num2);


	lines[n].output.kind = INTEGER; 

	if (num1 > num2) {
		lines[n].output.var.intvar = 1; 
	} else {
	       	lines[n].output.var.intvar = 0; 
	}

	free(s_num1); 
	free(s_num2); 

}

void equal(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(5,sizeof(char)); 
	char* s_num2 = calloc(5,sizeof(char)); 

	s_num1 = get_subdata(lines[n],0); 
	s_num2 = get_subdata(lines[n],strlen(s_num1)+1);

	int num1 = atoi(s_num1); 
	int num2 = atoi(s_num2);


	lines[n].output.kind = INTEGER; 

	if (num1 == num2) {
		lines[n].output.var.intvar = 1; 
	} else {
	       	lines[n].output.var.intvar = 0; 
	}

	free(s_num1); 
	free(s_num2); 

}



void cmp(int n, lines_t* lines, ...) {

	va_list args; 
	va_start(args,lines); 
        
	compiler_t* compiler = va_arg(args,compiler_t*); 

	char* condition = calloc(5,sizeof(char)); 
	char* output = calloc(5,sizeof(char));
        char* elseo = calloc(5,sizeof(char)); 	

	condition = get_subdata(lines[n],0); 
	output = get_subdata(lines[n],strlen(condition)+1);
	elseo = get_subdata(lines[n], strlen(condition)+strlen(output)+2); 

//	printf("condition: %s\n", condition); 
//	printf("output: %s\n", output);

	if (lines[atoi(condition)].output.var.intvar) {
	//	printf("TRUE\n");
		lines[n].line_data = output; 
		go_to(n,lines,compiler); 
	} else {
		lines[n].line_data = elseo; 
		go_to(n,lines,compiler); 
	}

	free(condition); 
	free(output); 
}
	
		


hash_map_t commands[] = {
	{"print", print},
	{"add", add}, 
	{"sub",sub},
	{"mul",mul},
	{"div",divide},
	{"goto",go_to},
	{"<", less_than},
	{">", greater_than},
	{"==", equal},
	{"cmp",cmp}
};

int COMMAND_LEN = 10; 
