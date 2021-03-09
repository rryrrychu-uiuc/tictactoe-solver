#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>
#include <cctype>

#include "tictactoe/tictactoe.h"

namespace tictactoe {

Board::Board(const std::string& board) {

  double boardDimension = sqrt(board.size());

  if (boardDimension > kMaxBoardDim_) {
    throw std::invalid_argument("Input string length exceeds maximum limit");
  } else if (boardDimension - floor(boardDimension) != 0) {
    throw std::invalid_argument("Input string length must be a perfect square");
  } else if (boardDimension < kMinBoardDim_) {
      throw std::invalid_argument("Input string length exceeds maximum limit");
  }

  kBoardDim_ = static_cast<int>(boardDimension);

  InitializeBoard(board);
  PrintBoard();
}

BoardState Board::EvaluateBoard() {

  if(!HasValidNumOfMarks()) {
    return BoardState::UnreachableState;
  }

  std::string winners = DetermineAllPossibleWinners();

  int x_wins = CountWinners(winners, 'x');
  int o_wins = CountWinners(winners, 'o');
  int total_x = CountMarks('x');
  int total_o = CountMarks('o');
  int difference = total_x - total_o;

  if(x_wins >= 1 && o_wins >= 1) {
    return BoardState::UnreachableState;
  } else if (x_wins >= 1) {
    return validXWin(difference);
  } else if (o_wins >= 1) {
    return validOWin(difference);
  } else {
    return BoardState::NoWinner;
  }
}

void Board::InitializeBoard(const std::string& board) {

  boardState_.resize(kBoardDim_);

  for (int index = 0; index < kBoardDim_; index++) {
    boardState_[index].resize(kBoardDim_);
  }

  for (int row = 0; row < kBoardDim_; row++) {
    for (int col = 0; col < kBoardDim_; col++) {
      int index = (row*3) + col;
      char target = tolower(board[index]);
      if (!IsXorO(target)) {
        boardState_[row][col] = '.';
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

  for (int row = 0; row < (int)kBoardDim_; row++) {
    for (int col = 0; col < (int)kBoardDim_; col++) {
      std::cout << boardState_[row][col];
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int Board::CountMarks(char target_letter) {

  int count = 0;
  for (int row = 0; row < kBoardDim_; row++) {
    for (int col = 0; col < kBoardDim_; col++) {
      if(boardState_[row][col] == target_letter) {
        count++;
      }
    }
  }

  return count;
}

int Board::CountWinners(std::string possible_winners, char winning_mark) {

  int winners = 0;
  for(int index = 0; index < (int)possible_winners.size(); index++) {
    if(possible_winners[index] == winning_mark) {
      winners++;
    }
  }

  return winners;
}

bool Board::HasValidNumOfMarks() {

  int x_marks = CountMarks('x');
  int o_marks = CountMarks('o');

  int mark_difference = x_marks - o_marks;
  return mark_difference == 0 || mark_difference == 1;
}

std::string Board::FindRowWins() {

  std::string possible_winners;

  for(int row = 0; row < kBoardDim_; row++) {
    char row_winner = DetermineWinner(row, 0, 0, 1);
    possible_winners += row_winner;
  }

  return possible_winners;
}

std::string Board::FindColWins() {
  std::string possible_winners;

  for(int col = 0; col < kBoardDim_; col++) {
    char col_winner = DetermineWinner(0, col, 1, 0);
    possible_winners += col_winner ;
  }

  return possible_winners;
}

char Board::FindLDiagonalWins() {
  return DetermineWinner(0,0,1,1);
}

char Board::FindRDiagonalWins() {
  return DetermineWinner(0, kBoardDim_ - 1, 1, -1);
}

char Board::DetermineWinner(int start_row, int start_col, int row_increment, int col_increment){

  char possible_winner = boardState_[start_row][start_col];

  if(!IsXorO(possible_winner)) {
    return ' ';
  }

  int iterator = 0;
  int row = start_row + row_increment;
  int col = start_col + col_increment;
  while (iterator < kBoardDim_ - 1) {

    if(boardState_[row][col] != possible_winner) {
      return ' ';
    }

    row += row_increment;
    col += col_increment;
    iterator++;
  }

  return possible_winner;
}

std::string Board::DetermineAllPossibleWinners() {

  std::string allWinners;
  allWinners.append(FindRowWins());
  allWinners.append(FindColWins());
  allWinners += FindLDiagonalWins();
  allWinners += FindRDiagonalWins();

  return allWinners;
}

BoardState Board::validXWin(int difference) {

  if(difference == 1) {
    return BoardState::Xwins;
  } else {
    return BoardState::UnreachableState;
  }
}

BoardState Board::validOWin(int difference){

  if (difference == 0) {
    return BoardState::Owins;
  } else {
    return BoardState::UnreachableState;
  }
}

}  // namespace tictactoe
