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

TEST_CASE("Boards with no winner") {
  SECTION("Full board with no winner") {
    REQUIRE(Board("xxoooxxxo").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("placeholder") {

  }
}
