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
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard() const;

 private:
  const size_t MAX_BOARD_DIM = 3;
  const size_t MIN_BOARD_DIM = 3;
  size_t BOARD_DIM;
  std::vector<std::vector<char>> boardState_;

  void InitializeBoard(const std::string& board);
  void PrintBoard();

  bool IsXorO(char evaluate);
  bool HasValidNumOfMarks(int x_marks, int o_marks);

  char DetermineWinner(int start_index, int increment_interval);

  std::string FindLDiagonalWins();
  std::string FindRDiagonalWins();
  std::string FindRowWins();
  std::string FindColWins();
};

}  // namespace tictactoe
