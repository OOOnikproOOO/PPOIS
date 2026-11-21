#include <gtest/gtest.h>
#include <sstream>
#include "Bootloader.h"
#include "ComputerException.h"
#include "POSTFailureException.h"

TEST(BootloaderTest, ConstructorAndGetters) {
    BIOSSettings bios("UEFI", true, true, false);
    Bootloader bl("GRUB2", 5, false, bios);
    EXPECT_EQ(bl.GetBootloaderName(), "GRUB2");
    EXPECT_EQ(bl.GetTimeoutSeconds(), 5);
    EXPECT_FALSE(bl.IsVerified());
    EXPECT_EQ(bl.GetBiosSettings(), bios);
}

TEST(BootloaderTest, TimeoutAndKernelVerification) {
    Bootloader bl;
    bl.SetTimeout(10);
    EXPECT_EQ(bl.GetTimeoutSeconds(), 10);
    EXPECT_THROW(bl.SetTimeout(-1), ComputerException);
    EXPECT_THROW(bl.SetTimeout(61), ComputerException);

    EXPECT_TRUE(bl.VerifyAndLoadKernel());
    EXPECT_TRUE(bl.IsVerified());

    bl.ResetVerification();
    EXPECT_FALSE(bl.IsVerified());

    bl.GetBiosSettings().SetBootMode("Legacy");
    EXPECT_THROW(bl.VerifyAndLoadKernel(), POSTFailureException);
}

TEST(BootloaderTest, EqualityAndStream) {
    Bootloader b1("GRUB2", 5, false);
    Bootloader b2("GRUB2", 5, false);
    Bootloader b3("rEFInd", 3, true);

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
    EXPECT_TRUE(b1 != b3);

    std::ostringstream oss;
    oss << b1;
    EXPECT_NE(oss.str().find("GRUB2"), std::string::npos);
}