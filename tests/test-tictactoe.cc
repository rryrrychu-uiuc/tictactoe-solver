#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }

  SECTION("String is too large") {
    REQUIRE_THROWS_AS(Board(".........."), std::invalid_argument);
  }

  SECTION("String is not a perfect square") {
    REQUIRE_THROWS_AS(Board("........"), std::invalid_argument);
  }

}

TEST_CASE("Edge case input types") {

  SECTION("String consists of weird characters") {
    REQUIRE_THROWS_AS(Board("@%tk1oxoo"), std::invalid_argument);
  }

  SECTION("String has character casing") {
    REQUIRE_THROWS_AS(Board("OxxOOXoXO"), std::invalid_argument);
  }

}

TEST_CASE("Boards with no winner") {
  SECTION("Full board with no winner") {
    REQUIRE(Board("xxoooxxxo").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Partial board with no winner") {
    REQUIRE(Board("x........").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Empty board with no winner") {
    REQUIRE(Board(".........").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("Boards with UnreachableState") {
  SECTION("Impossible multiple winners") {
    REQUIRE(Board("xxxooo...").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Impossible partial board") {
    REQUIRE(Board("xx.......").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Impossible full board") {
    REQUIRE(Board("xxoxoxxoo").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Too many winninng X marks") {
    REQUIRE(Board("xxxxoo...").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Too many winning O marks") {
    REQUIRE(Board("oooxx....").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Too many losing X marks") {
    REQUIRE(Board("xoxxox.o.").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Too many losing O marks") {
    REQUIRE(Board("xxxoo...o").EvaluateBoard() == BoardState::UnreachableState);
  }
}

