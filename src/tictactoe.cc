#include "tictactoe/tictactoe.h"

#include <cctype>
#include <cmath>
#include <stdexcept>

using std::invalid_argument;
using std::string;

namespace tictactoe {

Board::Board(const string& board) {
  double boardDimension = sqrt(board.size());

  if (boardDimension > kMaxBoardDim_) {
    throw invalid_argument("Input string length exceeds maximum limit");
  } else if (boardDimension - floor(boardDimension) != 0) {
    throw invalid_argument("Input string length must be a perfect square");
  } else if (boardDimension < kMinBoardDim_) {
    throw invalid_argument("Input string length exceeds maximum limit");
  }

  kBoardDim_ = static_cast<int>(boardDimension);
  InitializeBoard(board);
}

BoardState Board::EvaluateBoard() {
  int mark_num_difference = DetermineDifferenceInMarks();
  if (!HasValidNumOfMarks(mark_num_difference)) {
    return BoardState::UnreachableState;
  }

  return DetermineBoardState(mark_num_difference);
}

void Board::InitializeBoard(const string& board) {
  ResizeBoard();

  // maps every character in the string to a location on the array
  // in row-major order (row by row)
  for (int row = 0; row < kBoardDim_; row++) {
    for (int col = 0; col < kBoardDim_; col++) {
      int index = (row * kBoardDim_) + col;
      SetBoardValue(row, col, tolower(board[index]));
    }
  }
}

void Board::ResizeBoard() {
  boardState_.resize(kBoardDim_);
  for (int index = 0; index < kBoardDim_; index++) {
    boardState_[index].resize(kBoardDim_);
  }
}

void Board::SetBoardValue(int row, int col, char value) {
  if (!IsXorO(value)) {
    boardState_[row][col] = ' ';
  } else {
    boardState_[row][col] = value;
  }
}

const BoardState Board::DetermineBoardState(int mark_difference) {
  string winners = GenerateAllPossibleWinners();
  int x_wins = CountCharacters(winners, 'x');
  int o_wins = CountCharacters(winners, 'o');

  if (x_wins >= 1 && o_wins >= 1) {
    return BoardState::UnreachableState;
  } else if (x_wins >= 1) {
    return validXWin(mark_difference);
  } else if (o_wins >= 1) {
    return validOWin(mark_difference);
  } else {
    return BoardState::NoWinner;
  }
}

const int Board::DetermineDifferenceInMarks() {
  int x_marks = 0;
  int o_marks = 0;

  // count the number of x's and o's
  for (int row = 0; row < kBoardDim_; row++) {
    for (int col = 0; col < kBoardDim_; col++) {
      if (boardState_[row][col] == 'x') {
        x_marks++;
      } else if (boardState_[row][col] == 'o') {
        o_marks++;
      }
    }
  }

  return x_marks - o_marks;
}

const char Board::DetermineWinner(int start_row, int start_col,
                                  int row_increment, int col_increment) {
  // if the starting location is not an x or o, there is no winner
  char possible_winner = boardState_[start_row][start_col];
  if (!IsXorO(possible_winner)) {
    return ' ';
  }

  // steps through every location based on parameters
  // ensuring the marks are the same
  int iterator = 0;
  int row = start_row + row_increment;
  int col = start_col + col_increment;
  while (iterator < kBoardDim_ - 1) {
    if (boardState_[row][col] != possible_winner) {
      return ' ';
    }

    row += row_increment;
    col += col_increment;
    iterator++;
  }

  return possible_winner;
}

const string Board::FindRowWins() {
  string possible_winners;

  // the starting location to check if a row has a win
  // always starts at col zero and check each proceeding col in the same row
  // then shifting to the next row
  for (int row = 0; row < kBoardDim_; row++) {
    possible_winners += DetermineWinner(row, 0, 0, 1);
  }

  return possible_winners;
}

const string Board::FindColWins() {
  string possible_winners;

  // the starting location to check if a col has a win
  // always starts at row zero and check each proceeding row in the same col
  // then shifting to the next column
  for (int col = 0; col < kBoardDim_; col++) {
    possible_winners += DetermineWinner(0, col, 1, 0);
  }

  return possible_winners;
}

const char Board::FindLDiagonalWins() {
  // always start checking at the top left,
  // moving one row down and one col right each time
  return DetermineWinner(0, 0, 1, 1);
}

const char Board::FindRDiagonalWins() {
  // always start checking at the top right,
  // moving one row down and one col left each time
  return DetermineWinner(0, kBoardDim_ - 1, 1, -1);
}

const string Board::GenerateAllPossibleWinners() {
  string allWinners;

  allWinners.append(FindRowWins());
  allWinners.append(FindColWins());
  allWinners += FindLDiagonalWins();
  allWinners += FindRDiagonalWins();

  return allWinners;
}

const int Board::CountCharacters(string& possible_winners, char winning_mark) {
  int winners = 0;
  for (int index = 0; index < (int)possible_winners.size(); index++) {
    if (possible_winners[index] == winning_mark) {
      winners++;
    }
  }
  return winners;
}

const bool Board::HasValidNumOfMarks(int mark_difference) {
  return mark_difference == 0 || mark_difference == 1;
}

const bool Board::IsXorO(char evaluate) {
  return evaluate == 'x' || evaluate == 'o';
}

const BoardState Board::validXWin(int difference) {
  // x only wins when it has one more mark than the o
  if (difference == 1) {
    return BoardState::Xwins;
  } else {
    return BoardState::UnreachableState;
  }
}

const BoardState Board::validOWin(int difference) {
  // o only wins when it has the same number of marks as x
  if (difference == 0) {
    return BoardState::Owins;
  } else {
    return BoardState::UnreachableState;
  }
}

}  // namespace tictactoe
