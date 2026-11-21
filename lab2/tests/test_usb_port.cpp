#include <gtest/gtest.h>
#include <sstream>
#include "USBPort.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

TEST(USBPortTest, ConstructorAndGetters) {
    USBPort port("Type-A", "USB 3.0", false, "");
    EXPECT_EQ(port.GetPortType(), "Type-A");
    EXPECT_EQ(port.GetProtocolVersion(), "USB 3.0");
    EXPECT_FALSE(port.IsConnected());
    EXPECT_TRUE(port.GetConnectedDevice().empty());
    EXPECT_DOUBLE_EQ(port.CalculateMaxTransferRateMBs(), 625.0);
}

TEST(USBPortTest, ConnectAndDisconnect) {
    USBPort port;
    port.ConnectDevice("Flash Drive");
    EXPECT_TRUE(port.IsConnected());
    EXPECT_EQ(port.GetConnectedDevice(), "Flash Drive");

    EXPECT_THROW(port.ConnectDevice(""), ComputerException);
    EXPECT_THROW(port.ConnectDevice("Mouse"), ComputerException);

    port.DisconnectDevice();
    EXPECT_FALSE(port.IsConnected());
    EXPECT_THROW(port.DisconnectDevice(), DeviceNotFoundException);
}

TEST(USBPortTest, ProtocolSpeedCalculations) {
    USBPort usb4("Type-C", "USB4", false);
    EXPECT_DOUBLE_EQ(usb4.CalculateMaxTransferRateMBs(), 5000.0);

    USBPort usb2("Type-A", "USB 2.0", false);
    EXPECT_DOUBLE_EQ(usb2.CalculateMaxTransferRateMBs(), 60.0);
}

TEST(USBPortTest, EqualityAndStream) {
    USBPort u1("Type-C", "USB 3.2", true, "Headset");
    USBPort u2("Type-C", "USB 3.2", true, "Headset");
    USBPort u3("Type-A", "USB 2.0", false, "");

    EXPECT_TRUE(u1 == u2);
    EXPECT_FALSE(u1 == u3);
    EXPECT_TRUE(u1 != u3);

    std::ostringstream oss;
    oss << u1;
    EXPECT_NE(oss.str().find("Headset"), std::string::npos);
}