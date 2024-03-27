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


void saveWords(dict_t* dict) {
  int i, points, pp;
  //clear old file
  remove("results.txt");
  //open new file
  FILE* file;
  file = fopen("results.txt", "w");

  points = 0;
  //copy words from dict to file
  for (i = 0; i < dict->repetitions; i++) {
    pp = strlen(dict->rep[i]);
    fprintf(file, "word: %s, points: %d\n", dict->rep[i], pp);
    points = points + pp;
  }

  //print the number of words in results
  if (dict->repetitions == 0) {
    printf("No words found for this table\n");
  }
  else {
    printf("-> results.txt\n");
    printf("%d words founded with %d points scored\n", dict->repetitions, points);
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
        printf("%s: %d points\n", word, strlen(word));
        strcpy(dict->rep[dict->repetitions], word);
        dict->repetitions++;
      }
    }
    else if (dict->repetitions == 0) {
      printf("%s: %d points\n", word, strlen(word));
      strcpy(dict->rep[dict->repetitions], word);
      dict->repetitions = 1;
    }
  }

  //recursive call
  int row, col;
  //traverse cells, using the switch reduce the grid of one by one and improve search time of one order of magnitude
  if (r == 0) {
      for (row = r; row <= r + 1 && row < board.rows; row++){
        if (c == 0) {        
            for (col = c; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        else if (c == 1) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        else if (c == 2) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        else {
            for (col = c - 1; col <= c && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
      }
  }
  else if (r == 1) {
      for (row = r - 1 ; row <= r + 1 && row < board.rows; row++) {
        if (c == 0) {
            for (col = c; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        if (c == 1) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        if (c == 2) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        else {
            for (col = c - 1; col <= c && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
      }
  }
  else if (r == 2) {
      for (row = r - 1 ; row <= r + 1 && row < board.rows; row++){
        if (c == 0) {
            for (col = c; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        if (c == 1) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        if (c == 2) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        else {
            for (col = c - 1; col <= c && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
      }
  }
  else {
    for (row = r - 1 ; row <= r && row < board.rows; row++){
        if (c == 0) {
            for (col = c; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        if (c == 1) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        if (c == 2) {
            for (col = c - 1; col <= c + 1 && col < board.cols; col++){
              if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
                findWordsRec(n, row, col, board, dict, word);
              }
            }
        }
        else {
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
  char word[MAXWORDLENGTH] = "";
  char car;
  printBoard(board);
  for (r = 0; r<board.rows; r++) {
    for (c = 0; c<board.cols; c++) {
      findWordsRec(0, r, c, board, &dict, word);
    }
  }
  saveWords(&dict);
}

int main() {
  clock_t begin = clock();
  dict_t dict;
  dict = createDict();
  //srand(time(NULL));
  board_t board;
  board = generateBoard(ROWS, COLS);
  //printf("%d\n", strcmp("xénophobie", "xenophobie"));
  findWords(board, dict);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time used: %f\n", time_spent);
}
