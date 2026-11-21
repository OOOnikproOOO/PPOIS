#include <gtest/gtest.h>
#include <sstream>
#include "NetworkPacket.h"
#include "ComputerException.h"

TEST(NetworkPacketTest, ConstructorAndGetters) {
    NetworkPacket packet("10.0.0.1", "10.0.0.2", 80, 128, "TCP");
    EXPECT_EQ(packet.GetSourceIp(), "10.0.0.1");
    EXPECT_EQ(packet.GetDestIp(), "10.0.0.2");
    EXPECT_EQ(packet.GetPort(), 80);
    EXPECT_EQ(packet.GetPayloadBytes(), 128);
    EXPECT_EQ(packet.GetProtocol(), "TCP");
    EXPECT_FALSE(packet.IsSecurePort());
}

TEST(NetworkPacketTest, ResizeAndSecurePortCheck) {
    NetworkPacket p443("192.168.1.5", "1.1.1.1", 443, 64, "TCP");
    EXPECT_TRUE(p443.IsSecurePort());

    p443.ResizePayload(256);
    EXPECT_EQ(p443.GetPayloadBytes(), 256);
    EXPECT_THROW(p443.ResizePayload(-1), ComputerException);
}

TEST(NetworkPacketTest, EqualityAndStream) {
    NetworkPacket p1("1.2.3.4", "5.6.7.8", 22, 10, "TCP");
    NetworkPacket p2("1.2.3.4", "5.6.7.8", 22, 10, "TCP");
    NetworkPacket p3("1.2.3.4", "5.6.7.8", 80, 10, "TCP");

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_NE(oss.str().find("TCP"), std::string::npos);
}