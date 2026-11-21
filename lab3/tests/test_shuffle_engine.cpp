/**
 * @file test_shuffle_engine.cpp
 * @brief Unit tests for ShuffleEngine class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "ShuffleEngine.h"

TEST(ShuffleEngineTest, ConstructorAndGetters) {
    ShuffleEngine engine(12345, true);
    EXPECT_EQ(engine.GetSeed(), 12345u);
    EXPECT_TRUE(engine.IsEnabled());
    EXPECT_EQ(engine.GetShuffledSize(), 0u);
}

TEST(ShuffleEngineTest, PermutationGeneration) {
    ShuffleEngine engine(42, true);
    engine.GenerateShuffle(5);
    EXPECT_EQ(engine.GetShuffledSize(), 5u);

    const auto& order = engine.GetShuffledOrder();
    std::vector<bool> seen(5, false);
    for (size_t idx : order) {
        ASSERT_LT(idx, 5u);
        seen[idx] = true;
    }
    for (bool s : seen)
        EXPECT_TRUE(s);

    size_t next_idx = engine.GetNextShuffledIndex(0);
    EXPECT_LT(next_idx, 5u);
}

TEST(ShuffleEngineTest, ResetAndToggle) {
    ShuffleEngine engine;
    engine.GenerateShuffle(10);
    EXPECT_EQ(engine.GetShuffledSize(), 10u);

    engine.Reset();
    EXPECT_EQ(engine.GetShuffledSize(), 0u);
    EXPECT_EQ(engine.GetNextShuffledIndex(0), 0u);

    engine.ToggleShuffle(true);
    EXPECT_TRUE(engine.IsEnabled());
}

TEST(ShuffleEngineTest, EqualityAndStream) {
    ShuffleEngine s1(42, false);
    ShuffleEngine s2(42, false);
    ShuffleEngine s3(99, false);

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}