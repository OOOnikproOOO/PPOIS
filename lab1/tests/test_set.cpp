/**
 * @file test_set.cpp
 * @brief Модульные тесты для класса Set с использованием GoogleTest.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Set.h"

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

TEST(SetTest, FormSetFromStringAppendAndEdgeCases) {
    Set s1;
    s1.FormSetFromString("{a, b}", true);
    s1.FormSetFromString("{c}", false);
    EXPECT_EQ(s1.Size(), 3);
    EXPECT_TRUE(s1["c"]);

    Set s2;
    s2.FormSetFromString("{}", true);
    EXPECT_TRUE(s2.IsEmpty());

    s2.FormSetFromString("{x,,y}", true);
    EXPECT_TRUE(s2["x"]);
    EXPECT_TRUE(s2["y"]);
}

TEST(SetTest, MissingBranchesCoverage) {
    Set s1, s2, sub;
    sub.Add("inner");
    s1.Add(sub);

    EXPECT_TRUE(s1 != s2);

    Set sub2;
    sub2.Add("not_exist");
    EXPECT_FALSE(s1.Delete(sub2));

    s2.Add(sub);
    Set diff = s1 - s2;
    EXPECT_FALSE(diff[sub]);
}

TEST(SetTest, MissingOperatorCoverage) {
    Set s1, s2;
    s1.Add("A");
    s2.Add("A");
    s2.Add("B");

    EXPECT_FALSE(s1 == s2);

    Set s3, s4;
    s3.Add("A");
    s4.Add("B");

    EXPECT_FALSE(s3 == s4);

    EXPECT_FALSE(s1.IsEmpty());
}

TEST(SetTest, MathOperatorsWithSubsets) {
    Set s1, s2, sub1, sub2;
    sub1.Add("inner1");
    sub2.Add("inner2");

    s1.Add(sub1);
    s2.Add(sub1);
    s2.Add(sub2);

    Set u = s1 + s2;
    EXPECT_EQ(u.Size(), 2);

    Set i = s1 * s2;
    EXPECT_EQ(i.Size(), 1);

    Set d = s2 - s1;
    EXPECT_EQ(d.Size(), 1);

    s1 += s2;
    EXPECT_EQ(s1.Size(), 2);

    s1 -= s2;
    EXPECT_TRUE(s1.IsEmpty());
}