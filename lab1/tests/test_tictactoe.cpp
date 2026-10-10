/**
 * @file tests.cpp
 * @brief Модульные тесты для класса TicTacToe с использованием GoogleTest.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "TicTacToe.h"

TEST(TicTacToeTest, ConstructorAndGetters) {
    TicTacToe game(4);
    EXPECT_EQ(game.GetSize(), 4);
    EXPECT_EQ(game.GetActivePlayer(), 'X');
}

TEST(TicTacToeTest, IndexOperatorReadAndWrite) {
    TicTacToe game(3);
    game[1][1] = 'X';
    EXPECT_EQ(game[1][1], 'X');
    EXPECT_EQ(game[0][0], ' ');
}

TEST(TicTacToeTest, ValidMoveChecking) {
    TicTacToe game(3);
    EXPECT_FALSE(game.IsValidMove(5, 5));
    EXPECT_TRUE(game.IsValidMove(0, 0));

    game[0][0] = 'O';
    EXPECT_FALSE(game.IsValidMove(0, 0));
}

TEST(TicTacToeTest, PlayerSwitching) {
    TicTacToe game;
    EXPECT_EQ(game.GetActivePlayer(), 'X');
    game.SwitchPlayer();
    EXPECT_EQ(game.GetActivePlayer(), 'O');
}

TEST(TicTacToeTest, CheckWinRowsAndColumns) {
    TicTacToe game_row(3);
    game_row[1][0] = 'X'; game_row[1][1] = 'X'; game_row[1][2] = 'X';
    EXPECT_EQ(game_row.CheckWin(), 'X');

    TicTacToe game_col(3);
    game_col[0][2] = 'O'; game_col[1][2] = 'O'; game_col[2][2] = 'O';
    EXPECT_EQ(game_col.CheckWin(), 'O');
}

TEST(TicTacToeTest, CheckWinDiagonals) {
    TicTacToe game_main(3);
    game_main[0][0] = 'X'; game_main[1][1] = 'X'; game_main[2][2] = 'X';
    EXPECT_EQ(game_main.CheckWin(), 'X');

    TicTacToe game_anti(3);
    game_anti[0][2] = 'O'; game_anti[1][1] = 'O'; game_anti[2][0] = 'O';
    EXPECT_EQ(game_anti.CheckWin(), 'O');
}

TEST(TicTacToeTest, DrawLogicAndReset) {
    TicTacToe game(3);
    game[0][0] = 'X'; game[0][1] = 'O'; game[0][2] = 'X';
    game[1][0] = 'X'; game[1][1] = 'X'; game[1][2] = 'O';
    game[2][0] = 'O'; game[2][1] = 'X'; game[2][2] = 'O';

    for (int i = 0; i < 9; i++) game.SwitchPlayer();

    EXPECT_EQ(game.CheckWin(), ' ');
    EXPECT_TRUE(game.IsDraw());

    game.Reset();
    EXPECT_FALSE(game.IsDraw());
    EXPECT_EQ(game.GetActivePlayer(), 'X');
    EXPECT_EQ(game[0][0], ' ');
}

TEST(TicTacToeTest, EqualityOperators) {
    TicTacToe g1(3), g2(3), g3(4);
    EXPECT_TRUE(g1 == g2);
    EXPECT_FALSE(g1 == g3);
    EXPECT_TRUE(g1 != g3);

    g1[0][0] = 'X';
    EXPECT_FALSE(g1 == g2);
}

TEST(TicTacToeTest, IOStreams) {
    std::stringstream input("4");
    TicTacToe game(3);
    input >> game;
    EXPECT_EQ(game.GetSize(), 4);

    std::stringstream input_bad("1");
    input_bad >> game;
    EXPECT_EQ(game.GetSize(), 3);

    std::stringstream output;
    game[0][0] = 'X';
    output << game;
    EXPECT_NE(output.str().find("X"), std::string::npos);

}

TEST(TicTacToeTest, InvalidMovesAndInequality) {
    TicTacToe game(3);

    game[0][0] = 'X';
    EXPECT_FALSE(game.IsValidMove(0, 0));

    TicTacToe game2(3);
    EXPECT_TRUE(game != game2);
}