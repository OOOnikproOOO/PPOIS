#include <gtest/gtest.h>
#include <sstream>
#include "Keyboard.h"
#include "ComputerException.h"

TEST(KeyboardTest, ConstructorAndGetters) {
    Keyboard kbd("ENG", "Mechanical Blue", true);
    EXPECT_EQ(kbd.GetLayout(), "ENG");
    EXPECT_EQ(kbd.GetSwitchType(), "Mechanical Blue");
    EXPECT_TRUE(kbd.IsBacklightOn());
    EXPECT_TRUE(kbd.GetInputBuffer().empty());
}

TEST(KeyboardTest, TypeTextAndBuffer) {
    Keyboard kbd;
    EXPECT_EQ(kbd.GetLayout(), "ENG");
    kbd.TypeText("Hello ");
    kbd.TypeText("World!");
    EXPECT_EQ(kbd.GetInputBuffer(), "Hello World!");

    kbd.ClearBuffer();
    EXPECT_TRUE(kbd.GetInputBuffer().empty());

    kbd.ToggleBacklight(false);
    EXPECT_FALSE(kbd.IsBacklightOn());

    kbd.SetLayout("RUS");
    EXPECT_EQ(kbd.GetLayout(), "RUS");
    EXPECT_THROW(kbd.SetLayout(""), ComputerException);
}

TEST(KeyboardTest, EqualityAndStream) {
    Keyboard k1("US", "Red", true);
    Keyboard k2("US", "Red", true);
    Keyboard k3("DE", "Brown", false);

    EXPECT_TRUE(k1 == k2);
    EXPECT_FALSE(k1 == k3);
    EXPECT_TRUE(k1 != k3);

    std::ostringstream oss;
    oss << k1;
    EXPECT_NE(oss.str().find("Red"), std::string::npos);
}