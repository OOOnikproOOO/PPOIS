#include <gtest/gtest.h>
#include <sstream>
#include "SystemClock.h"
#include "ComputerException.h"

TEST(SystemClockTest, ConstructorAndGetters) {
    SystemClock clock(3665, 3, true);
    EXPECT_EQ(clock.GetUptimeSeconds(), 3665);
    EXPECT_EQ(clock.GetTimezoneOffsetHours(), 3);
    EXPECT_TRUE(clock.IsNtpSynced());
    EXPECT_EQ(clock.FormatUptime(), "01:01:05");
}

TEST(SystemClockTest, TickTimezoneAndSync) {
    SystemClock clock(0, 0, false);
    clock.Tick(125);
    EXPECT_EQ(clock.GetUptimeSeconds(), 125);
    EXPECT_EQ(clock.FormatUptime(), "00:02:05");
    EXPECT_THROW(clock.Tick(-10), ComputerException);

    clock.SetTimezoneOffset(-5);
    EXPECT_EQ(clock.GetTimezoneOffsetHours(), -5);
    EXPECT_THROW(clock.SetTimezoneOffset(-13), ComputerException);
    EXPECT_THROW(clock.SetTimezoneOffset(15), ComputerException);

    clock.SyncWithNtp();
    EXPECT_TRUE(clock.IsNtpSynced());
}

TEST(SystemClockTest, EqualityAndStream) {
    SystemClock c1(100, 3, true);
    SystemClock c2(100, 3, true);
    SystemClock c3(200, -4, false);

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_TRUE(c1 != c3);

    std::ostringstream oss;
    oss << c1;
    EXPECT_NE(oss.str().find("UTC+3"), std::string::npos);
}