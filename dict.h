#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXWORDLENGTH 16
#define MINWORDLENGTH 3
//#define MAXWORDS 370105
#define MAXWORDS 1000
#define POSSREPETITIONS 30

typedef struct dict {
  int nb;
  int repetitions;
  char * rep[POSSREPETITIONS];
  char * words[MAXWORDS];
} dict_t;

/*
dict_t createRep() {
  dict_t repetitions;
  int i;
  for (i = 0; i<MAXWORDS; i++) {
    repetitions.words[i] = malloc(sizeof(char[MAXWORDLENGTH]));
    assert(repetitions.words[i]);
  }
  repetitions.nb = 0;

  return repetitions;
}
*/
dict_t createDict() {
  dict_t dict;
  
  // words.txt file is a dictionary to choose words from
  FILE* file;
  file = fopen("words1000.txt", "r");
  if (!file){
      printf("file not found!\n");
      exit(EXIT_FAILURE);
  }
  
  // copy words from file to dict
  char * line;
  size_t len = 0;
  ssize_t read;
  int i;

  for (i = 0; i < MAXWORDS; i++) {
    dict.words[i] = malloc(sizeof(char[MAXWORDLENGTH]));
    assert(dict.words[i]);
  }
  for (i = 0; i < POSSREPETITIONS; i++) {
    dict.rep[i] = malloc(sizeof(char[MAXWORDLENGTH]));
    assert(dict.rep[i]);
  }
  

  i = 0;
  while ((read = getline(&line, &len, file)) != -1) {
    if (MINWORDLENGTH <= read <= MAXWORDLENGTH) {
      strcpy(dict.words[i], line);
      dict.words[i][strlen(dict.words[i])-1] = '\0';
      i++;
    }
  }
  dict.nb = i;
  dict.repetitions = 0;

  fclose(file);

  return dict;
}


void printDict (dict_t dict){
  int i;

  for (i = 0; i < dict.nb; i++){ 
    printf("%d: %s\n", i, dict.words[i]);
  }
}

//tmp main function for debugging
/*
int main() {
  dict_t dict;
  dict = createDict();
  printDict(dict);
}
*/



