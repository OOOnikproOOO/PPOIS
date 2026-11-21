#include <gtest/gtest.h>
#include <sstream>
#include "Mouse.h"
#include "ComputerException.h"

TEST(MouseTest, ConstructorAndGetters) {
    Mouse mouse(800, 100, 200, false, false);
    EXPECT_EQ(mouse.GetDpi(), 800);
    EXPECT_EQ(mouse.GetCursorX(), 100);
    EXPECT_EQ(mouse.GetCursorY(), 200);
    EXPECT_FALSE(mouse.IsLeftButtonPressed());
    EXPECT_FALSE(mouse.IsRightButtonPressed());
}

TEST(MouseTest, MoveAndClick) {
    Mouse mouse(1600, 0, 0);
    mouse.Move(50, 80);
    EXPECT_EQ(mouse.GetCursorX(), 50);
    EXPECT_EQ(mouse.GetCursorY(), 80);

    mouse.Move(-100, -100);
    EXPECT_EQ(mouse.GetCursorX(), 0);
    EXPECT_EQ(mouse.GetCursorY(), 0);

    mouse.ClickLeft();
    EXPECT_TRUE(mouse.IsLeftButtonPressed());
    mouse.ReleaseLeft();
    EXPECT_FALSE(mouse.IsLeftButtonPressed());

    mouse.ClickRight();
    EXPECT_TRUE(mouse.IsRightButtonPressed());
    mouse.ReleaseRight();
    EXPECT_FALSE(mouse.IsRightButtonPressed());

    mouse.SetDpi(3200);
    EXPECT_EQ(mouse.GetDpi(), 3200);
    EXPECT_THROW(mouse.SetDpi(50), ComputerException);
    EXPECT_THROW(mouse.SetDpi(50000), ComputerException);
}

TEST(MouseTest, EqualityAndStream) {
    Mouse m1(1600, 10, 20);
    Mouse m2(1600, 10, 20);
    Mouse m3(800, 0, 0);

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
    EXPECT_TRUE(m1 != m3);

    std::ostringstream oss;
    oss << m1;
    EXPECT_NE(oss.str().find("1600"), std::string::npos);
}