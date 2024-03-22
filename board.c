#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//print the board values in the terminal
void printBoard (board_t b) {
  int i, j;

  for (i = 0; i<b.rows; i++) {
    for (j = 0; j<b.cols; j++) {
      printf("rows %d, col %d, val %c, seen %d | \n", i, j, b.car[i][j], b.seen[i][j]);
      printf("- \n");
    }
  }
}

//give back a random letter 
char randLetter() {
  char * az = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int r = rand();
  r = r % 27;
  
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
int main() {
  board_t b;
  b = generateBoard(4, 4);
  printBoard(b);
}
