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

  // change the size of boardState_ to match the initialized dimension size
  void ResizeBoard();

  // change the value at a certain location given a location and value
  void SetBoardValue(int row, int col, char value);

  // determine if passed char is an x or o
  auto IsXorO(char evaluate) -> bool;

  // determine if the balance between the number of x's and o's are correct
  auto HasValidNumOfMarks(int mark_difference) -> bool;

  // given a starting location and how much/in what direction to increment in
  // return 'x', 'o', or ' ' (no winner) depending on who wins
  auto DetermineWinner(int start_row, int start_col, int row_increment,
                       int col_increment) -> char;

  // return string of all possible winners from every row, column and diagonal
  auto GenerateAllPossibleWinners() -> std::string;

  // return difference in Xs and Os
  auto DetermineDifferenceInMarks() -> int;

  // find which mark won for the left diagonal
  auto FindLDiagonalWins() -> char;

  // find which mark won for the left diagonal
  auto FindRDiagonalWins() -> char;

  // find which mark won in each row
  auto FindRowWins() -> std::string;

  // find which mark won in each column
  auto FindColWins() -> std::string;

  // return the number of the passed character in a passed string
  auto CountCharacters(std::string possible_winners, char winning_mark) -> int;

  // return a board state depending on whether there is a valid difference in
  // marks for x and o wins
  auto validXWin(int difference) -> BoardState;
  auto validOWin(int difference) -> BoardState;
};

}  // namespace tictactoe
