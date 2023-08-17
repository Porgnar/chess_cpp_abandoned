#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(){

system("clear");

printf("Welcome to Prognar's shit 2player chess game.\nIt can't even tell checkmates yet :(\nIf you want to quit the game type the word 'quit' without hyphens of course.\nTry to have fun if you can.\nBut before any fun can be had choose an OS\n\tw - for windows\n\tl - for linux\n");






while(1){

char input[5];
char *prog;
scanf("%s",input);


if(input[0]=='w'){
	
	char p[10]="./wc.exe";
	prog=p;
	
	char *args[]={prog,NULL};
	execvp(args[0],args);

}else if(input[0]=='l'){

	char p[10]="./lc";
	prog=p;
	
	char *args[]={prog,NULL};
	execvp(args[0],args);

}else{printf("Come on....choose properly!\n");}

}

return 0;
}

