#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "dict.h"


typedef struct result {
  char * words[MAXWORDS];
} result_t;

int points(dict_t* dict) {
  int i, j, points, len;
  points = 0;

  for (i=0; i<dict->repetitions; i++) {
    len = strlen(dict->rep[i]);
    points = points + len;
  }
  printf("In %d words, the game scored %d points\n", dict->repetitions, points);
}

void saveWords(dict_t* dict) {
  int i;
  //clear old file
  remove("results.txt");
  //open new file
  FILE* file;
  file = fopen("results.txt", "w");

  //copy words from dict to file
  for (i = 0; i < dict->repetitions; i++) {
    fprintf(file, "word: %s, points: %d\n", dict->rep[i], strlen(dict->rep[i]));
  }

  //print the number of words in results
  if (dict->repetitions == 0) {
    printf("No words found for this table\n");
  }
  else {
    printf("-> results.txt\n");
  }
}

int valid(char * word, dict_t* dict) {
  int i, n, bottom, top, cmp;
  n = 0;
  i = (dict->nb)/2;
  bottom = 0;
  top = dict->nb;
  
  //2*10 = 1024 -> reduce the number of elements of 3 orders of magnitude
  while (n < 10) {
    cmp = strcmp(word, dict->words[i]);
    if (cmp == 0) {
      return 1;
    }
    else if (cmp < 0) {
      top = i;
      i = i/2;
    }
    else if (cmp > 0) {
      bottom = i;
      i = i/2;
    }
    n++;
  }

  for (i=bottom; i<top; i++) {
    if (strcmp(dict->words[i], word) == 0) {
      return 1;
    }
  }
  return 0;
}


void findWordsRec(int n, int r, int c, board_t board, dict_t* dict, char* word) {
  int x, len, not_in;
  not_in = 1;
  //set visited value
  board.seen[r][c] = 1;

  //add current car to word
  char car;
  car = board.car[r][c];
  
  len = strlen(word);
  word[len] = car;
  
  //check if word is in dict and if is it a repetition
  if (valid(word, dict)) {
    if (dict->repetitions > 0) {
      for (x = 0; x < POSSREPETITIONS; x++) {
        if (strcmp(word, dict->rep[x]) == 0) {
          not_in = 0;
        }
      }
      if (not_in) {
        printf("%s\n", word);
        strcpy(dict->rep[dict->repetitions], word);
        dict->repetitions++;
      }
    }
    else if (dict->repetitions == 0) {
      printf("%s\n", word);
      strcpy(dict->rep[dict->repetitions], word);
      dict->repetitions = 1;
    }
  }

  //recursive call
  int row, col;
  //traverse cells, using the switch reduce the grid of one by one and improve search time of one order of magnitude
  switch (r) {
    case 0:
      for (row = r; row <= r + 1 && row < board.rows; row++){
        switch (c) {        
          case 0:
            for (col = c; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          case 1:
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          case 2:
            for (col = c - 1; col <= c && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          }
      }
    case 1:
      for (row = r - 1 ; row <= r + 1 && row < board.rows; row++) {
        switch (c) {        
          case 0:
            for (col = c; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          case 1:
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          case 2:
            for (col = c - 1; col <= c && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          }
      }
    case 2:
      for (row = r - 1 ; row <= r && row < board.rows; row++){
        switch (c) {        
          case 0:
            for (col = c; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          case 1:
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          case 2:
            for (col = c - 1; col <= c && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
          }
        }
      }

  //reset current cell
  word[len] = '\0';
  board.seen[r][c] = 0;
}

void findWords(board_t board, dict_t dict) {
  int r, c, i, len;
  char word[16] = "";
  char car;
  printBoard(board);
  for (r = 0; r<board.rows; r++) {
    for (c = 0; c<board.cols; c++) {
      findWordsRec(0, r, c, board, &dict, word);
    }
  }
  saveWords(&dict);
  points(&dict);
}

int main() {
  dict_t dict;
  dict = createDict();
  srand(time(NULL));
  board_t board;
  board = generateBoard(ROWS, COLS);
  printf("%d\n", strcmp("xénophobie", "xenophobie"));
  findWords(board, dict);
}
