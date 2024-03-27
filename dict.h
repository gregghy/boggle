#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXWORDLENGTH 16
#define MAXWORDS 3000
//number of words possible in one table
#define POSSREPETITIONS 30

typedef struct dict {
  int nb;
  int repetitions;
  char * rep[POSSREPETITIONS];
  char * words[MAXWORDS];
} dict_t;

int defineLang() {
  int result;
  printf("Type 0 for the ENG wordlist, type 1 for the FR wordlist: ");
  scanf("%d", &result);
  return result;
}

dict_t createDict() {
  dict_t dict;
  
  //chose the file to choose words from
  FILE* file;
  int lang;
  lang = defineLang();

  while (lang != 0 && lang != 1) {
    printf("Error in language choice, please enter 0 or 1\n");
    lang = defineLang();
  }
  if (lang == 0) {
    file = fopen("words3000.txt", "r");
  }
  else {
    file = fopen("words3000fr.txt", "r");
  }
  
  if (!file){
      printf("FATAL ERROR: wordlist not found!\n");
      exit(EXIT_FAILURE);
  }
  
  char * line;
  size_t len = 0;
  ssize_t read;
  int i;

  //memory allocation for the dictionary
  for (i = 0; i < MAXWORDS; i++) {
    dict.words[i] = malloc(sizeof(char[MAXWORDLENGTH]));
    assert(dict.words[i]);
  }

  //memory allocation for the repetitions
  for (i = 0; i < POSSREPETITIONS; i++) {
    dict.rep[i] = malloc(sizeof(char[MAXWORDLENGTH]));
    assert(dict.rep[i]);
  }
  
  //copy the words from file to dict
  i = 0;
  while ((read = getline(&line, &len, file)) != -1) {
    if (read <= MAXWORDLENGTH) {
      strcpy(dict.words[i], line);
      dict.words[i][strlen(dict.words[i])-1] = '\0';
      i++;
    }
  }

  //set number of words and repetitions
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
  //dict_t dict;
  //dict = createDict();
  //printDict(dict);
  defineLang();
}
*/




