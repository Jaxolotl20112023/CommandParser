#include "hashMap.h"

char* get_subdata(char* str, int offset) {
	char* temp = calloc(20,sizeof(char));


	for (int i=offset; i<strlen(str); i++) {

		if (str[i] == ',' || str[i] == '\n') {
			break; 
		}

//		printf("line_data char at %d: %c\n",i,lines[n].line_data[i]);
		
		temp[i-offset] = str[i];
	
	}
	return temp; 
}

int get_char_total(char* str, char item) {

	int appearance = 0;

	for (int i=0; i<strlen(str); i++) {

		if (str[i] == item) {
			appearance++; 
		}
	}

	return appearance; 
}


int get_char_index(char* str, char item, int offset) {

	int appearance = 0; 

	for (int i=0; i<strlen(str); i++) {

		if (str[i] == item) {
		//	printf("%c is at %d!\n",item,i);
			appearance++; 
		}
		if (appearance == offset) {
			return i;
		}
	}
	
	return -1; 

}

char* put_substring(char* str, char* n, int index) {
	
	int strLen = strlen(str); 
	int nlen = strlen(n); 
	char* new_str = calloc(strLen+nlen,sizeof(char));

//	printf("new string length: %d", strlen(new_str));

	int j=0;
	int k=0; 	

	for (int i=0; i<strLen+nlen; i++) {
		
		if (i >= index && i < index+nlen) {
			new_str[i] = n[k]; 
//			printf("new chars to str: %c\n",new_str[i]); 
			k++; 
			continue; 
		}

		new_str[i] = str[j];

//		printf("new chars to str: %c\n",new_str[i]); 
	        j++;	
	}	

	return new_str; 
}	

char* new_replace(char* str, char* old, char* new) {

	int strLen = strlen(str); 
	int oldlen = strlen(old); 
	int newlen = strlen(new); 
	int index_str_len = (strLen-oldlen)+newlen; 
	
//	printf("index str len: %d\n",index_str_len);
//	printf("new str len: %d\n",newlen);
//	printf("old str len: %d\n",oldlen);
	
	int i=0;
	int j=0;
	int k=0; 
	int len_dif = abs(newlen - oldlen); 

	int search = 1; 

	char* index = calloc(index_str_len,sizeof(char)); 

	while (1) {

		//printf("old %c at %d\n",old[k],k);

		if (str[j] == old[k] && search) {
			k++; 
//			printf("MATCH\n");
		} else { 
			k=0; 
		}

		if (k == oldlen) {
//		        printf("match at %c\n",str[j]);
			
//			printf("at i:%d\n",i);

//			printf("i-(oldlen+1): %d\n",(i-oldlen)+1); 
//			printf("i-newlen: %d\n", i-newlen);
			
			int max = newlen >= oldlen ? i+len_dif : i-len_dif; 
//			printf("max: %d\n",max);
//			printf("min: %d\n",(i-oldlen)+1);	
			for(int l=(i-oldlen)+1; l<=max; l++) {
//				printf("k index: %d k value: %c\n",l-(i-oldlen+1),new[l-(i-oldlen+1)]);
				index[l] = new[l-(i-oldlen+1)]; 
				k++;
//			        printf("i: %d, %c\n",l,index[l]);	
			}
			i = max+1;
			search = 0;
//			printf("before j: %d\n",j);
//		        printf("j %d\n",j);	
			j++;
		}


		index[i] = str[j];

		if (index[i] == '\0') break; 

//		printf("i: %d, %c\n",i,index[i]);
		j++; 
		i++;
	}

//	printf("new index: %s\n",index);

	return index; 
}


int check_var(int n, lines_t* lines) {

//	printf("in check var!");
	
	char* index = NULL;	
	char* str = lines[n].line_data; 
	int total_vars = get_char_total(str,'@');
	int num = 1;
//        printf("\ntotal vars: %d\n", total_vars);	

	while (num <= total_vars) {

	//	printf("num %d out of %d\n", num,total_vars);

		int target = get_char_index(lines[n].line_data,'@',1);

	//	printf("\nline: %d and TARGET index: %d\n", n,target);
     	  // 	printf("length of line_data: %d\n",strlen(lines[n].line_data));	

		int i = target+1; 

		if (target != -1) {

		       char* index = (char*)calloc(5,sizeof(char));
	//	       printf("start searching!!\n");

	//	       printf("starting value at %d = %c\n",i,lines[n].line_data[i]);

		       while (1) {

			       if (lines[n].line_data[i] == ' ' || lines[n].line_data[i] == ',' || lines[n].line_data[i] == '\0') {
					break; 
		               }

			       index[i-(target+1)] = lines[n].line_data[i];
	//		       printf("Index char: %c\n",index[i-(target+1)]);  
			       i++;
	       	       }
	  
	//	       printf("lines data: %s\n",lines[n].line_data);
	//	       printf("index val: %s\n",index);
	//	       printf("why\n");	      
	//	       printf("index strlen: %d\n", strlen(index)); 

		       int f_new = lines[atoi(index)].output.var.floatvar;
		       char new[20]; 
		       snprintf(new, sizeof(new), "%d", f_new);

	//	       printf("value of line %d: %s\n",atoi(index),new);

		       index = put_substring(index,"@",0);
	//	       printf("index with @ symbol: %s\n",index); 

//		       printf("New: %s", new);  
			

		       lines[n].line_data = new_replace(lines[n].line_data,index,new);
	//	       printf("offset: %d\n",1);
	//	       printf("at target index: %c\n", lines[n].line_data[target]);
	///	       printf("target: %d\n",target);

		       //lines[n].line_data[target] = ' ';
		      // memmove(&lines[n].line_data[target], &lines[n].line_data[target+1], strlen(lines[n].line_data) - target);  
	//	       printf("new lines_data: %s\n", lines[n].line_data);

		       num++;

		} else {
		       num++; 
		}
	}

	if (index != NULL) free(index); 

}


void print(int n, lines_t* lines, ...) {
	
	printf("%s",lines[n].line_data); 

}

void add(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0;

	s_num1 = get_subdata(lines[n].line_data, 0); 
	s_num2 = get_subdata(lines[n].line_data,strlen(s_num1)+1); 

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1+num2; 

	free(s_num1); 
	free(s_num2);

}

void sub(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0; 

	s_num1 = get_subdata(lines[n].line_data, 0); 
	s_num2 = get_subdata(lines[n].line_data,strlen(s_num1)+1); 

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1-num2; 

	free(s_num1); 
	free(s_num2);

}

void mul(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0; 

	s_num1 = get_subdata(lines[n].line_data, 0); 
	s_num2 = get_subdata(lines[n].line_data,strlen(s_num1)+1); 	
	
	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1*num2; 

	free(s_num1); 
	free(s_num2);

}

void divide(int n, lines_t* lines, ...) {

	char* s_num1 = calloc(20,sizeof(char));
	char* s_num2 = calloc(20,sizeof(char)); 
	float num1 = 0;
	float num2 = 0; 

	s_num1 = get_subdata(lines[n].line_data, 0); 
	s_num2 = get_subdata(lines[n].line_data,strlen(s_num1)+1);

	num1 = atoi(s_num1); 
	num2 = atoi(s_num2); 

	lines[n].output.kind = FLOAT;
	lines[n].output.var.floatvar = num1/num2; 

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



	va_end(args); 
}

void less_than(int n, lines_t* lines, ...) {


	char* s_num1 = calloc(5,sizeof(char)); 
	char* s_num2 = calloc(5,sizeof(char));


	s_num1 = get_subdata(lines[n].line_data,0); 
	s_num2 = get_subdata(lines[n].line_data,strlen(s_num1)+1);

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

	s_num1 = get_subdata(lines[n].line_data,0); 
	s_num2 = get_subdata(lines[n].line_data,strlen(s_num1)+1);

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

	s_num1 = get_subdata(lines[n].line_data,0); 
	s_num2 = get_subdata(lines[n].line_data,strlen(s_num1)+1);

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

	condition = get_subdata(lines[n].line_data,0); 
	output = get_subdata(lines[n].line_data,strlen(condition)+1);
	elseo = get_subdata(lines[n].line_data, strlen(condition)+strlen(output)+2); 

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
