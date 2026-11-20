/**
 * @file test_sleep_timer.cpp
 * @brief Unit tests for SleepTimer class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "SleepTimer.h"

TEST(SleepTimerTest, ConstructorAndGetters) {
    SleepTimer timer(45, 20, true, false);
    EXPECT_EQ(timer.GetRemainingMinutes(), 45);
    EXPECT_EQ(timer.GetFadeoutDurationSec(), 20);
    EXPECT_TRUE(timer.ShouldFadeout());
    EXPECT_FALSE(timer.IsActive());
}

TEST(SleepTimerTest, StartTickAndExpiration) {
    SleepTimer timer;
    timer.Start(30, true);
    EXPECT_TRUE(timer.IsActive());
    EXPECT_EQ(timer.GetRemainingMinutes(), 30);

    timer.TickMinutes(10);
    EXPECT_EQ(timer.GetRemainingMinutes(), 20);
    EXPECT_TRUE(timer.IsActive());

    timer.TickMinutes(25);
    EXPECT_EQ(timer.GetRemainingMinutes(), 0);
    EXPECT_FALSE(timer.IsActive());
    EXPECT_TRUE(timer.IsExpired());

    timer.Start(15);
    EXPECT_TRUE(timer.IsActive());
    timer.Cancel();
    EXPECT_FALSE(timer.IsActive());
}

TEST(SleepTimerTest, EqualityAndStream) {
    SleepTimer t1(30, 10, true, true);
    SleepTimer t2(30, 10, true, true);
    SleepTimer t3(15, 10, true, true);

    EXPECT_EQ(t1, t2);
    EXPECT_NE(t1, t3);

    std::ostringstream oss;
    oss << t1;
    EXPECT_FALSE(oss.str().empty());
}