#include <gtest/gtest.h>
#include <sstream>
#include "SecurityFirewall.h"
#include "ComputerException.h"

TEST(SecurityFirewallTest, ConstructorAndGetters) {
    SecurityFirewall fw(true, "Medium", 0);
    EXPECT_TRUE(fw.IsEnabled());
    EXPECT_EQ(fw.GetSecurityLevel(), "Medium");
    EXPECT_EQ(fw.GetBlockedPacketsCount(), 0);
    EXPECT_TRUE(fw.IsPortAllowed(80));
    EXPECT_TRUE(fw.IsPortAllowed(443));
    EXPECT_FALSE(fw.IsPortAllowed(6667));
}

TEST(SecurityFirewallTest, InspectPacketAndPortRules) {
    SecurityFirewall fw(true, "Strict");
    NetworkPacket valid_pkt("10.0.0.1", "10.0.0.2", 443, 64, "TCP");
    EXPECT_TRUE(fw.InspectPacket(valid_pkt));

    NetworkPacket rogue_pkt("1.1.1.1", "10.0.0.2", 9999, 50, "TCP");
    EXPECT_THROW(fw.InspectPacket(rogue_pkt), ComputerException);
    EXPECT_EQ(fw.GetBlockedPacketsCount(), 1);

    fw.AllowPort(9999);
    EXPECT_TRUE(fw.InspectPacket(rogue_pkt));

    fw.RevokePort(9999);
    EXPECT_THROW(fw.InspectPacket(rogue_pkt), ComputerException);

    fw.ToggleFirewall(false);
    EXPECT_FALSE(fw.IsEnabled());
    EXPECT_TRUE(fw.InspectPacket(rogue_pkt));

    EXPECT_THROW(fw.AllowPort(-1), ComputerException);
    EXPECT_THROW(fw.AllowPort(70000), ComputerException);
}

TEST(SecurityFirewallTest, EqualityAndStream) {
    SecurityFirewall f1(true, "Medium", 0);
    SecurityFirewall f2(true, "Medium", 0);
    SecurityFirewall f3(false, "Low", 5);

    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
    EXPECT_TRUE(f1 != f3);

    std::ostringstream oss;
    oss << f1;
    EXPECT_NE(oss.str().find("ACTIVE"), std::string::npos);
}