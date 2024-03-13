#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void printBoard (board_t b) {
  int i, j;

  for (i = 0; i<b -> rows; i++) {
    for (j = 0; j<b -> cols; j++) {
      printf("%d | \n", b -> car[i][j]);
      printf("- \n");
    }
  }
}

board_t generateBoard (int r, int c){
  int i, j;
  board_t b;
  b = malloc(sizeof(board_t));
  b->rows = r;
  b->cols = c;

  for (i=0; i<r; i++) {
    for (j=0; j<c; j++) {
      printf("i = %d ", i);
      printf("j = %d\n", j);
      b -> car[i][j] = 20;
      b -> seen[i][j] = 0;
    }
  }
  return b;
}

int main() {
  board_t b;
  b = generateBoard(4, 4);
  printBoard(b);
}
