#include <gtest/gtest.h>
#include <sstream>
#include "UserAccount.h"
#include "ComputerException.h"

TEST(UserAccountTest, ConstructorAndGetters) {
    UserAccount user("nikita", "Administrator", false);
    EXPECT_EQ(user.GetUsername(), "nikita");
    EXPECT_EQ(user.GetRole(), "Administrator");
    EXPECT_FALSE(user.IsLoggedIn());
    EXPECT_EQ(user.GetFailedLoginAttempts(), 0);

    user.SetUsername("newNikita");
    EXPECT_EQ(user.GetUsername(), "newNikita");
    EXPECT_THROW(user.SetUsername(""), ComputerException);
}

TEST(UserAccountTest, AuthenticationAndLockout) {
    UserAccount user("student", "StandardUser", false, "pass123");
    EXPECT_FALSE(user.Login("wrong"));
    EXPECT_EQ(user.GetFailedLoginAttempts(), 1);
    EXPECT_FALSE(user.Login("wrong2"));
    EXPECT_EQ(user.GetFailedLoginAttempts(), 2);

    EXPECT_THROW(user.Login("wrong3"), ComputerException);

    user.ResetAttempts();
    EXPECT_EQ(user.GetFailedLoginAttempts(), 0);
    EXPECT_TRUE(user.Login("pass123"));
    EXPECT_TRUE(user.IsLoggedIn());

    UserAccount user2("student2", "StandardUser", false, "pass123");
    EXPECT_FALSE(user2.Login("wrong"));
    EXPECT_EQ(user2.GetFailedLoginAttempts(), 1);
    EXPECT_TRUE(user2.Login("pass123"));
    EXPECT_EQ(user2.GetFailedLoginAttempts(), 0);
    EXPECT_TRUE(user2.IsLoggedIn());

    user2.ChangePassword("pass123", "newSecret");
    EXPECT_THROW(user2.ChangePassword("wrong", "newSecret"), ComputerException);
    EXPECT_THROW(user2.ChangePassword("newSecret", "12"), ComputerException);

    user2.Logout();
    EXPECT_FALSE(user2.IsLoggedIn());
}

TEST(UserAccountTest, EqualityAndStream) {
    UserAccount u1("admin", "Administrator", true, "1234");
    UserAccount u2("admin", "Administrator", true, "1234");
    UserAccount u3("guest", "Guest", false, "0000");

    EXPECT_TRUE(u1 == u2);
    EXPECT_FALSE(u1 == u3);
    EXPECT_TRUE(u1 != u3);

    std::ostringstream oss;
    oss << u1;
    EXPECT_NE(oss.str().find("admin"), std::string::npos);
}