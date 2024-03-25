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

int valid(char * word, dict_t* dict) {
  //dict_t dict;
  int i, len;
  //dict = createDict();
  len = strlen(word);
  char * alf = "abcdefghijklmnopqrstuvwxyz";
  for (i=0; i<dict->nb; i++) {
    if (strcmp(dict->words[i], word) == 0) {
      return 1;
    }
  }
  return 0;
}


void findWordsRec(int n, int r, int c, board_t board, dict_t* dict, char* word) {
  printf("n: %d \n", n);
  n++;
  printBoard(board);
  printf("word: %s\n", word);
  int x, len;

  //set visited value
  board.seen[r][c] = 1;

  //add current car to word
  char car;
  car = board.car[r][c];
  
  len = strlen(word);
  word[len] = car;
  //printf("i: %d, j: %d\n", r, c);
  //printf("seen: %d, char: %c\n", board.seen[r][c], car);
  
  //check if word is in dict TODO make more efficient
  if (valid(word, dict)) {
    printf("%s\n", word);
  }

  //recursive call
  int row, col;
  //traverse cells
  for (row = r - 1 ; row <= r + 1 && row < board.rows; row++){
    printf("row: %d\n", row);
    for (col = c - 1; col <= c + 1 && col < board.cols; col++){
      printf("col: %d\n", col);
      if (((row >= 0 && col > 0) || (row > 0 && col >= 0)) && board.seen[row][col] == 0){
        printf("%c\n", board.car[row][col]);
        findWordsRec(n, row, col, board, dict, word);
      }
    }
  }

  //reset current cell
  word[len] = '\0';
  board.seen[r][c] = 0;
}

void findWords(board_t board, dict_t dict) {
  int r, c, x, len;
  char word[32] = "";
  char car;
  //dict_t dict;
  //dict = createDict();
  for (r = 0; r<board.rows; r++) {
    for (c = 0; c<board.cols; c++) {
      findWordsRec(0, r, c, board, &dict, word);
    }
  }
}

int main() {
  dict_t dict;
  dict = createDict();
  board_t board;
  board = generateBoard(4, 4);
  findWords(board, dict);
}
