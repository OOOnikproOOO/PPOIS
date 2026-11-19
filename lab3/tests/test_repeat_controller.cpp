/**
 * @file test_repeat_controller.cpp
 * @brief Unit tests for RepeatController class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "RepeatController.h"

TEST(RepeatControllerTest, ConstructorAndGetters) {
    RepeatController rc("None", 5);
    EXPECT_EQ(rc.GetMode(), "None");
    EXPECT_EQ(rc.GetCycleCount(), 0);
    EXPECT_EQ(rc.GetMaxRepeats(), 5);
}

TEST(RepeatControllerTest, CycleModeProgression) {
    RepeatController rc;
    EXPECT_EQ(rc.GetMode(), "None");

    rc.CycleMode();
    EXPECT_EQ(rc.GetMode(), "RepeatAll");

    rc.CycleMode();
    EXPECT_EQ(rc.GetMode(), "RepeatOne");

    rc.CycleMode();
    EXPECT_EQ(rc.GetMode(), "None");
}

TEST(RepeatControllerTest, RepetitionLogicAndReset) {
    RepeatController rc("RepeatOne", 2);
    EXPECT_TRUE(rc.ShouldRepeatCurrent());

    rc.IncrementCycle();
    EXPECT_EQ(rc.GetCycleCount(), 1);
    EXPECT_TRUE(rc.ShouldRepeatCurrent());

    rc.IncrementCycle();
    EXPECT_EQ(rc.GetCycleCount(), 2);
    EXPECT_FALSE(rc.ShouldRepeatCurrent());

    rc.Reset();
    EXPECT_EQ(rc.GetCycleCount(), 0);
    EXPECT_EQ(rc.GetMode(), "None");
}

TEST(RepeatControllerTest, SetMode) {
    RepeatController rc;
    rc.SetMode("RepeatAll");
    EXPECT_EQ(rc.GetMode(), "RepeatAll");

    rc.SetMode("InvalidMode");
    EXPECT_EQ(rc.GetMode(), "RepeatAll");
}

TEST(RepeatControllerTest, EqualityAndStream) {
    RepeatController r1("RepeatAll");
    RepeatController r2("RepeatAll");
    RepeatController r3("None");

    EXPECT_EQ(r1, r2);
    EXPECT_NE(r1, r3);

    std::ostringstream oss;
    oss << r1;
    EXPECT_FALSE(oss.str().empty());
}