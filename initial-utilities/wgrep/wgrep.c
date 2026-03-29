#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
bool check(char* line , char* term){

	int i =0;
	int j =0;

	while(line[i]!='\n'){
		int start = i;
		while(line[start]==term[j]){
			start++;
			j++;
		}

		if(term[j]=='\0'){
			//matches
			return true;
		}
		else{
			j=0;
		}
		i++;
	}
	return false;
}


//aaad searchterm aad

int main(int argc, char* args[]){
	
	char* searchterm = args[1];
	//if no cmd argument then error
	if(argc<2){
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	else if(argc==2) {
		//if searchterm passed but no file passed then read from stdin
		char* line = NULL;
		size_t len =0;

		while(getline(&line,&len,stdin)!=-1){
			if(check(line,searchterm)){
				printf("%s",line);
			}
		}

		free(line);
	}


	//if file cannot be opened then print "wgrep: cannot open file\n" and exit with status 1
	//in all other cases exit with code 0
	//matching is case sensitive
	
	for(int i =2;i<argc;i++){
		
		//open a file for reading
		char *fname = args[i];
		FILE *file = fopen(fname,"r");
		
		if(file==NULL){
			printf("wgrep: cannot open file\n");
			exit(1);
		}
	
		//reading from file and finding searchterm
		char *line = NULL;
		size_t len =0;

		while(getline(&line,&len,file)!=-1){
			if(check(line,searchterm)){
				printf("%s",line);
			}
		}
			

		free(line);	
		//closing a file
		fclose(file);

	}

	return 0;
}
