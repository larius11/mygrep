#include "mygrep.h"

/**
 * This function checks if a character is a digit
 * @return 0 if not a digit, 1 otherwise
 **/
int isDigit(const char c){
	if((c<48)||(c>57))
		return 0;
	return 1;	
}