#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXWORDLENGTH 16
//#define MAXWORDS 370105
#define MAXWORDS 3000
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
  
  // words.txt file is a dictionary to choose words from
  FILE* file;
  int lang;
  lang = defineLang();
  if (lang == 0) {
    file = fopen("words3000.txt", "r");
  }
  else if (lang == 1) {
    file = fopen("words3000fr.txt", "r");
  }
  else {
    printf("Lang error\n");
    defineLang();
    createDict();
  }

  if (!file){
      printf("FATAL ERROR: wordlist not found!\n");
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
    if (read <= MAXWORDLENGTH) {
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
  //dict_t dict;
  //dict = createDict();
  //printDict(dict);
  defineLang();
}
*/




