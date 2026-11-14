#include <gtest/gtest.h>
#include <sstream>
#include "Computer.h"
#include "POSTFailureException.h"

TEST(ComputerTest, ConstructorAndGetters) {
    Computer pc("Workstation");
    EXPECT_EQ(pc.GetPcName(), "Workstation");
    EXPECT_FALSE(pc.IsPoweredOn());
    EXPECT_FALSE(pc.GetOS().IsBooted());
}

TEST(ComputerTest, PowerOnDiagnosticsAndShutdown) {
    Computer pc("Gaming Rig");
    pc.GetRAM().InstallStick(RAMStick("DDR4-3200", 16384, 3200, "DDR4"), 0);

    pc.PowerOn();
    EXPECT_TRUE(pc.IsPoweredOn());
    EXPECT_TRUE(pc.GetOS().IsBooted());
    EXPECT_TRUE(pc.GetPSU().IsPoweredOn());

    EXPECT_TRUE(pc.RunDiagnostics());

    pc.ConnectNetwork("192.168.1.150");
    EXPECT_TRUE(pc.GetNetwork().IsConnected());
    EXPECT_GT(pc.GetNetwork().GetBytesSent(), 0);

    pc.PowerOff();
    EXPECT_FALSE(pc.IsPoweredOn());
    EXPECT_FALSE(pc.GetOS().IsBooted());
    EXPECT_FALSE(pc.GetPSU().IsPoweredOn());
}

TEST(ComputerTest, PostFailureWithoutRam) {
    Computer empty_pc("NoRamPC");
    EXPECT_THROW(empty_pc.PowerOn(), POSTFailureException);
    EXPECT_FALSE(empty_pc.IsPoweredOn());
}

TEST(ComputerTest, EqualityAndStream) {
    Computer pc1("PC1");
    Computer pc2("PC1");
    Computer pc3("PC2");

    EXPECT_TRUE(pc1 == pc2);
    EXPECT_FALSE(pc1 == pc3);
    EXPECT_TRUE(pc1 != pc3);

    std::ostringstream oss;
    oss << pc1;
    EXPECT_NE(oss.str().find("PC1"), std::string::npos);
}