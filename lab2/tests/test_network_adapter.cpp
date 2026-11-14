#include <gtest/gtest.h>
#include <sstream>
#include "NetworkAdapter.h"
#include "ComputerException.h"

TEST(NetworkAdapterTest, ConstructorAndGetters) {
    NetworkAdapter nic("00:11:22:33:44:55", "192.168.0.10", 1000, true);
    EXPECT_EQ(nic.GetMacAddress(), "00:11:22:33:44:55");
    EXPECT_EQ(nic.GetIpAddress(), "192.168.0.10");
    EXPECT_EQ(nic.GetLinkSpeedMbps(), 1000);
    EXPECT_TRUE(nic.IsConnected());
    EXPECT_EQ(nic.GetBytesSent(), 0);
    EXPECT_EQ(nic.GetBytesReceived(), 0);
}

TEST(NetworkAdapterTest, SendReceiveAndDisconnect) {
    NetworkAdapter nic;
    NetworkPacket pkt("192.168.1.105", "8.8.8.8", 53, 100, "UDP");

    nic.SendPacket(pkt);
    EXPECT_EQ(nic.GetBytesSent(), 100);

    nic.ReceivePacket(pkt);
    EXPECT_EQ(nic.GetBytesReceived(), 100);

    nic.Disconnect();
    EXPECT_FALSE(nic.IsConnected());
    EXPECT_THROW(nic.SendPacket(pkt), ComputerException);
    EXPECT_THROW(nic.ReceivePacket(pkt), ComputerException);

    nic.Connect();
    EXPECT_TRUE(nic.IsConnected());
}

TEST(NetworkAdapterTest, EqualityAndStream) {
    NetworkAdapter n1("AA:BB:CC", "10.0.0.1", 1000, true);
    NetworkAdapter n2("AA:BB:CC", "10.0.0.1", 1000, true);
    NetworkAdapter n3("DD:EE:FF", "10.0.0.2", 2500, false);

    EXPECT_TRUE(n1 == n2);
    EXPECT_FALSE(n1 == n3);
    EXPECT_TRUE(n1 != n3);

    std::ostringstream oss;
    oss << n1;
    EXPECT_NE(oss.str().find("AA:BB:CC"), std::string::npos);
}