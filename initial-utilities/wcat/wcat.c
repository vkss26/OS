#include<stdio.h>
#include<stdlib.h>

int main(int argc , char* argv[]){

	if(argc<=1){
		exit(0);
	}

	for(int i =1;i<argc;i++){
		FILE* fptr = fopen(argv[i],"r");
		if(fptr==NULL){
			printf("wcat: cannot open file\n");
			exit(1);
		}
		char buffer[100000];
		while(fgets(buffer,sizeof(buffer),fptr)!=NULL){
			printf("%s",buffer);
		}
		fclose(fptr);
	}

return 0;
}
