#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8

char board[BOARD_SIZE][BOARD_SIZE];

void init_board() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = '-';
    }
  }
}

void print_board() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

int main() {
  init_board();
  print_board();
  return 0;
}
