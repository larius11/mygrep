#include "mygrep.h"

void set(char* str, char c){
	int i = 0;
	while(i<255){
		str[i++] = c;
	}
}