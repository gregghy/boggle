typedef struct board {
  int rows;
  int cols;
  int car[4][4];
  int seen[4][4];
} board_t;

void printBoard(board_t board);
board_t generateBoard(int r, int c);
