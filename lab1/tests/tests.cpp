/**
 * @file tests.cpp
 * @brief Модульные тесты для классов Set и TicTacToe с использованием GoogleTest.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Set.h"
#include "TicTacToe.h"

// Тесты для класса Set

TEST(SetTest, DefaultConstructorAndEmptyCheck) {
    Set s;
    EXPECT_TRUE(s.IsEmpty());
    EXPECT_EQ(s.Size(), 0);
}

TEST(SetTest, CopyConstructor) {
    Set s1;
    s1.Add("a");
    s1.Add("b");
    Set s2(s1);
    EXPECT_EQ(s2.Size(), 2);
    EXPECT_TRUE(s2["a"]);
    EXPECT_TRUE(s2 == s1);
}

TEST(SetTest, AssignmentOperator) {
    Set s1, s2;
    s1.Add("x");
    s2.Add("y");
    s2 = s1;
    EXPECT_EQ(s2.Size(), 1);
    EXPECT_TRUE(s2["x"]);

    s1 = s1;
    EXPECT_EQ(s1.Size(), 1);
}

TEST(SetTest, AddAndCheckStringElements) {
    Set s;
    EXPECT_TRUE(s.Add("apple"));
    EXPECT_FALSE(s.Add("apple"));
    EXPECT_EQ(s.Size(), 1);
    EXPECT_TRUE(s["apple"]);
    EXPECT_FALSE(s["banana"]);
}

TEST(SetTest, AddAndCheckSubsetElements) {
    Set s, subset;
    subset.Add("inner");

    EXPECT_TRUE(s.Add(subset));
    EXPECT_FALSE(s.Add(subset));
    EXPECT_EQ(s.Size(), 1);
    EXPECT_TRUE(s[subset]);
}

TEST(SetTest, DeleteStringAndSubset) {
    Set s, subset;
    s.Add("x");
    subset.Add("inner");
    s.Add(subset);

    EXPECT_TRUE(s.Delete("x"));
    EXPECT_FALSE(s.Delete("x"));
    EXPECT_FALSE(s["x"]);

    EXPECT_TRUE(s.Delete(subset));
    EXPECT_FALSE(s.Delete(subset));
    EXPECT_EQ(s.Size(), 0);
    EXPECT_TRUE(s.IsEmpty());
}

TEST(SetTest, FormSetFromStringParsing) {
    Set s;
    s.FormSetFromString("{a, b, {c}}", true);
    EXPECT_EQ(s.Size(), 3);
    EXPECT_TRUE(s["a"]);
    EXPECT_TRUE(s["b"]);

    Set subset;
    subset.Add("c");
    EXPECT_TRUE(s[subset]);
}

TEST(SetTest, BasicMathOperators) {
    Set s1, s2;
    s1.FormSetFromString("{1, 2}", true);
    s2.FormSetFromString("{2, 3}", true);

    Set u = s1 + s2;
    EXPECT_EQ(u.Size(), 3);

    Set i = s1 * s2;
    EXPECT_EQ(i.Size(), 1);
    EXPECT_TRUE(i["2"]);

    Set d = s1 - s2;
    EXPECT_EQ(d.Size(), 1);
    EXPECT_TRUE(d["1"]);
}

TEST(SetTest, CompoundMathOperators) {
    Set s1, s2;
    s2.Add("x");

    s1 += s2;
    EXPECT_EQ(s1.Size(), 1);
    EXPECT_TRUE(s1["x"]);

    Set s3;
    s3.Add("x");
    s3.Add("y");
    s1 *= s3;
    EXPECT_EQ(s1.Size(), 1);
    EXPECT_TRUE(s1["x"]);

    s1 -= s2;
    EXPECT_TRUE(s1.IsEmpty());
}

TEST(SetTest, BooleanGeneration) {
    Set s;
    s.Add("A");
    s.Add("B");
    Set bool_set = s.Boolean();
    EXPECT_EQ(bool_set.Size(), 4);
}

TEST(SetTest, IOStreams) {
    std::stringstream input("{test_val}");
    Set s;
    input >> s;
    EXPECT_TRUE(s["test_val"]);

    std::stringstream output;
    output << s;
    std::string out_str = output.str();
    EXPECT_NE(out_str.find("{"), std::string::npos);
    EXPECT_NE(out_str.find("test_val"), std::string::npos);
}

// Тесты для класса TicTacToe

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