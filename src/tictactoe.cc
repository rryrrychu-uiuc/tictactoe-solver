#include <stdexcept>
#include <string>
#include <math.h>
#include <iostream>
#include <ctype.h>

#include "tictactoe/tictactoe.h"

namespace tictactoe {

Board::Board(const std::string& board) {

  double boardDimension = sqrt(board.size());

  if (boardDimension > MAX_BOARD_DIM) {
    throw std::invalid_argument("Input string length exceeds maximum limit");
  } else if (boardDimension - floor(boardDimension) != 0) {
    throw std::invalid_argument("Input string length must be a perfect square");
  } else if (boardDimension < MIN_BOARD_DIM) {
      throw std::invalid_argument("Input string length exceeds maximum limit");
  }

  BOARD_DIM = (size_t)boardDimension;

  InitializeBoard(board);
  PrintBoard();
}

BoardState Board::EvaluateBoard() const {
  return BoardState::NoWinner;
}

void Board::InitializeBoard(const std::string& board) {

  boardState_.resize(BOARD_DIM);

  for (int index = 0; index < (int)BOARD_DIM; index++) {
    boardState_[index].resize(BOARD_DIM);
  }

  for (int row = 0; row < (int)BOARD_DIM; row++) {
    for (int col = 0; col < (int)BOARD_DIM; col++) {
      int index = (row*3) + col;
      char target = tolower(board[index]);
      if (!IsXorO(target)) {
        boardState_[row][col] = ' ';
      } else {
        boardState_[row][col] = target;
      }
    }
  }
}

bool Board::IsXorO(char evaluate) {

  return evaluate == 'x' || evaluate == 'o';
}

void Board::PrintBoard() {

  for (int row = 0; row < (int)BOARD_DIM; row++) {
    for (int col = 0; col < (int)BOARD_DIM; col++) {
      std::cout << boardState_[row][col];
    }
    std::cout << "\n";
  }
}


}  // namespace tictactoe
