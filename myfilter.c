#include <stdio.h>
#include <stdlib.h>

typedef enum { TRUE = 1, FALSE = 0 } bool;

int myfilter(char **pattern_grid, int sz){
	
	char buff[2560];

	while(fgets(buff, 2560, stdin)){

		int c = 0;
		while((buff[c]!='\n')&&(buff[c]!=EOF)&&(buff[c]!=0)){
			bool found_match = TRUE;
			for (int i = 0; i < sz; ++i){
				if((buff[c+i]=='\n')||(buff[c+i]==EOF)||(pattern_grid[i][buff[c+i]]!='1')){
					found_match = FALSE;
					break;
				}
			}
			if (found_match){
				printf("%s",buff);
				break;}
			++c;
		}
	}

	return 0;
}

/**
 * NAME:
 * 		myfilter - 
 *
 * SYNOPSIS:
 *		./myfilter
 *
 * DESCRIPTION:
 *
 *  	-
 **/