#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

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
  explicit Board(const string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard();

 private:
  const size_t kMaxBoardDim_ = 3;
  const size_t kMinBoardDim_ = 3;
  int kBoardDim_;
  vector<vector<char>> boardState_;

  void InitializeBoard(const string& board);

  // change the size of boardState_ to match the initialized dimension size
  void ResizeBoard();

  // change the value at a certain location given a location and value
  void SetBoardValue(int row, int col, char value);

  // returns the proper boardstate of the passed board
  const BoardState DetermineBoardState(int mark_difference);

  // return difference in Xs and Os
  const int DetermineDifferenceInMarks();

  // given a starting location and how much/in what direction to increment in
  // return 'x', 'o', or ' ' (no winner) depending on who wins
  const char DetermineWinner(int start_row, int start_col, int row_increment,
                             int col_increment);

  // find which mark won for the left diagonal
  const char FindLDiagonalWins();

  // find which mark won for the left diagonal
  const char FindRDiagonalWins();

  // find which mark won in each row
  const string FindRowWins();

  // find which mark won in each column
  const string FindColWins();

  // return string of all possible winners from every row, column and diagonal
  const string GenerateAllPossibleWinners();

  // return the number of the passed character in a passed string
  const int CountCharacters(string& possible_winners, char winning_mark);

  // determine if the balance between the number of x's and o's are correct
  const bool HasValidNumOfMarks(int mark_difference);

  // determine if passed char is an x or o
  const bool IsXorO(char evaluate);

  // return a board state depending on whether there is a valid difference in
  // marks for x and o wins
  const BoardState validXWin(int difference);
  const BoardState validOWin(int difference);
};

}  // namespace tictactoe
