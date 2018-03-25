#include <stdio.h>
#include <stdlib.h>

typedef enum { TRUE = 1, FALSE = 0 } bool;

char filename(char * arg, char * buff);
char otoc(char *str);

int mypattern(char * pattern, char * patfile);
int myfilter(char **pattern_grid, int sz);
int range(char *str, char* grid_row);
int isDigit(const char c);

void set(char* str, char c);