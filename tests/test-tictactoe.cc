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

  SECTION("Partial X move board with no winner") {
    REQUIRE(Board("x........").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Partial O move board with no winner") {
    REQUIRE(Board("x.....o...").EvaluateBoard() == BoardState::NoWinner);
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
    REQUIRE(Board("xoxxox.oo").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Too many losing O marks") {
    REQUIRE(Board("xxxoo...o").EvaluateBoard() == BoardState::UnreachableState);
  }
}

TEST_CASE("Boards with X Win") {

  SECTION("Valid X Win") {
    REQUIRE(Board("xxxoo....").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Valid X Multiple Wins") {
    REQUIRE(Board("xxxxooxoo").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Edge Row X Win") {
    REQUIRE(Board("...oo.xxx").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Middle Row X Win") {
    REQUIRE(Board("o..xxxo..").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Edge Column X Win") {
    REQUIRE(Board(".ox.ox..x").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Middle Column X Win") {
    REQUIRE(Board("ox..xo.x.").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Left Diagonal X Win") {
    REQUIRE(Board("x.o.x.o.x").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Right Diagonal X Win") {
    REQUIRE(Board("o.x.x.x.o").EvaluateBoard() == BoardState::Xwins);
  }



}

TEST_CASE("Boards with O Win"){

  SECTION("Valid O Win") {
    REQUIRE(Board("oooxx.x..").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Edge Row O Win") {
    REQUIRE(Board("...xx.ooo").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Middle Row O Win") {
    REQUIRE(Board("x..oooxx.").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Edge Column O Win") {
    REQUIRE(Board(".xoxxo..o").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Middle Column O Win") {
    REQUIRE(Board("xo.xox.o.").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Left Diagonal O Win") {
    REQUIRE(Board("o.x.oxx.o").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Right Diagonal O Win") {
    REQUIRE(Board("x.o.o.oxx").EvaluateBoard() == BoardState::Owins);
  }
}

