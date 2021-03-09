#pragma once

#include <string>
#include <vector>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  explicit Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard();

 private:
  const size_t kMaxBoardDim_ = 3;
  const size_t kMinBoardDim_ = 3;
  int kBoardDim_;
  std::vector<std::vector<char>> boardState_;

  void InitializeBoard(const std::string& board);
  void PrintBoard();

  auto IsXorO(char evaluate) -> bool;
  auto HasValidNumOfMarks() -> bool;
  auto DetermineWinner(int start_row, int start_col, int row_increment, int col_increment) -> char;
  auto DetermineAllPossibleWinners() -> std::string;
  auto CountMarks(char target_letter) -> int;
  auto CountWinners(std::string possible_winners, char winning_mark) -> int;
  auto validXWin(int difference) -> BoardState;
  auto validOWin(int difference) -> BoardState;

  auto FindLDiagonalWins() -> char;
  auto FindRDiagonalWins() -> char;
  auto FindRowWins() -> std::string;
  auto FindColWins() -> std::string;
};

}  // namespace tictactoe
