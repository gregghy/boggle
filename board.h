#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define ROWS 4
#define COLS 4

typedef struct board {
  int rows;
  int cols;
  char car[ROWS][COLS];
  int seen[ROWS][COLS];
} board_t;

//print the board values in the terminal
void printBoard (board_t b) {
  int i, j;

  for (i = 0; i<b.rows; i++) {
    for (j = 0; j<b.cols; j++) {
      printf(" %c |", b.car[i][j]);
    }
    printf("\n");
  }
}

//generate a random letter 
char randLetter() {
  char * az = "abcdefghijklmnopqrstuvwxyz";
  int r = rand();
  r = r % 26;
  
  char letter = az[r];

  return letter;
}

//generate the game board
board_t generateBoard (int r, int c){
  int i, j;
  board_t b;
  b.rows = r;
  b.cols = c;

  for (i=0; i<r; i++) {
    for (j=0; j<c; j++) {
      b.car[i][j] = randLetter();
      b.seen[i][j] = 0;
    }
  }
  return b;
}

//tmp main function for debugging
/*
int main() {
  board_t b;
  b = generateBoard(4, 4);
  printBoard(b);
}
*/
