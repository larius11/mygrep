#include <stdio.h>
#include <stdlib.h>

int mypattern(char * pattern, char * patfile);

char filename(char * arg, char * buff){
	if((arg[0]=='-')&&
		(arg[1]=='-')&&
		(arg[2]=='f')&&
		(arg[3]=='i')&&
		(arg[4]=='l')&&
		(arg[5]=='e')&&
		(arg[6]=='=')){
		int i = 7;
		if(!arg[i]){
			printf("Need a filename!\n");
			return 0;
		}

		while (arg[i]){
			buff[i-7] = arg[i];
			++i;
		}
		buff[i-7] = '\0';
		return 1;
	}
	printf("Invalid use of --file=<filename>.\n");
	return 0;
}

int main(int argc, char **argv)
{
	char patfile[100];
	char f = 0;
	int i = 1;
	while(argv[i]){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
				case 'f':
					++i;
					if(argv[i])
						mypattern("\0",argv[i]);
					else
						printf("Need a file name after -f.\n");
					break;
				case '-':
					if (filename(argv[i], patfile))
						mypattern("\0", patfile);
					break;
				default:
					printf("Not a valid argument: %s\n\n",argv[i]+1);	
			}
		}else{
			mypattern(argv[i],"\0");
		}
		++i;
	}
	return 0;
}


/**
 * NAME:
 * 		mygrep - 
 *
 * SYNOPSIS:
 *		./mygrep 
 *
 * DESCRIPTION:
 *
 *  	-
 **/