#include "dict.h"

dict_t createDict() {
  dict_t dict;
  int wordNB;
  // words.txt file is a dictionary to choose words from
  FILE* file;
  file = fopen("words.txt", "r");
  if (!file){
      printf("file not found!\n");
      exit(EXIT_FAILURE);
  }
  //count number of words

  // copy words from file to dict
  //TODO make this into hash-table to speed up the process (for example filter by first letter)
  char * line;
  size_t len = 32;
  ssize_t read;
  int i;

  for (i = 0; i < MAXWORDS; i++) {
    dict.words[i] = malloc(sizeof(char[MAXWORDLENGTH]));
    assert(dict.words[i]);
  }
  i = 0;
  while ((read = getline(&line, &len, file)) != -1) {
    if (read <= MAXWORDLENGTH) {
      if (read >= MINWORDLENGTH) {
        strcpy(dict.words[i], line);
        i++;
      }
    }
  }
  dict.nb = i;

  fclose(file);

  return dict;
}


void printDict (dict_t dict){
  int i;

  for (i = 0; i < dict.nb; i++){ 
    printf("%d: %s", i, dict.words[i]);
  }
}

int main() {
  dict_t dict;
  dict = createDict();
  //printDict(dict);

}
