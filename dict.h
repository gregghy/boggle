#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXWORDLENGTH 16
#define MAXWORDS 370105

typedef struct dict {
  int nb;
  char * words[MAXWORDS];
} dict_t;

dict_t createDict();
void printDict();
