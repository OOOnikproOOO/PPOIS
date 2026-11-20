/**
 * @file test_subscription_plan.cpp
 * @brief Unit tests for SubscriptionPlan class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "SubscriptionPlan.h"
#include "LicenseExpiredException.h"

TEST(SubscriptionPlanTest, ConstructorAndGetters) {
    SubscriptionPlan plan("HiFi", 1411, true, "2027.01.01");
    EXPECT_EQ(plan.GetTierName(), "HiFi");
    EXPECT_EQ(plan.GetMaxBitrateKbps(), 1411);
    EXPECT_TRUE(plan.AllowsOffline());
    EXPECT_EQ(plan.GetExpiryDate(), "2027.01.01");
}

TEST(SubscriptionPlanTest, OfflineAllowanceAndClamping) {
    SubscriptionPlan low_plan("Basic", 64, false, "2026.12.31");
    EXPECT_GE(low_plan.GetMaxBitrateKbps(), 128);
    EXPECT_FALSE(low_plan.AllowsOffline());

    SubscriptionPlan high_plan("Ultra", 2000, true, "2026.12.31");
    EXPECT_LE(high_plan.GetMaxBitrateKbps(), 1411);
    EXPECT_TRUE(high_plan.AllowsOffline());
}

TEST(SubscriptionPlanTest, ExpirationCheckAndUpgrade) {
    SubscriptionPlan plan("Premium", 320, true, "2026.06.30");
    EXPECT_FALSE(plan.CheckExpiration("2026.05.01"));
    EXPECT_THROW(plan.CheckExpiration("2026.07.01"), LicenseExpiredException);

    plan.Upgrade("HiFi", 1411, true, "2027.12.31");
    EXPECT_EQ(plan.GetTierName(), "HiFi");
    EXPECT_EQ(plan.GetMaxBitrateKbps(), 1411);
    EXPECT_NO_THROW(plan.CheckExpiration("2026.07.01"));
}

TEST(SubscriptionPlanTest, EqualityAndStream) {
    SubscriptionPlan p1("Premium", 320);
    SubscriptionPlan p2("Premium", 320);
    SubscriptionPlan p3("Free", 128);

    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_FALSE(oss.str().empty());
}