#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//print the board values in the terminal
void printBoard (board_t b) {
  int i, j;

  for (j = 0; j<b.cols; j++) {
    printf(" %c |", b.car[0][j]);
  }
  printf("\n");
  for (j = 0; j<b.cols; j++) {
    printf(" %c |", b.car[1][j]);
  }
  printf("\n");
  for (j = 0; j<b.cols; j++) {
    printf(" %c |", b.car[2][j]);
  }
  printf("\n");
  for (j = 0; j<b.cols; j++) {
    printf(" %c |", b.car[3][j]);
  }
  printf("\n");

}

//generate a random letter 
char randLetter() {
  char * az = "abcdefghijklmnopqrstuvwxyz";
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
