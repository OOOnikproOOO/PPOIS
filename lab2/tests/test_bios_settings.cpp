#include <gtest/gtest.h>
#include <sstream>
#include "BIOSSettings.h"
#include "ComputerException.h"
#include "POSTFailureException.h"

TEST(BIOSSettingsTest, ConstructorAndGetters) {
    BIOSSettings bios("UEFI", true, true, false);
    EXPECT_EQ(bios.GetBootMode(), "UEFI");
    EXPECT_TRUE(bios.IsXmpEnabled());
    EXPECT_TRUE(bios.IsSecureBootEnabled());
    EXPECT_FALSE(bios.IsFastBootEnabled());
}

TEST(BIOSSettingsTest, ModifyAndValidateConfig) {
    BIOSSettings bios;
    bios.ToggleXmp(false);
    bios.SetFastBoot(true);
    EXPECT_FALSE(bios.IsXmpEnabled());
    EXPECT_TRUE(bios.IsFastBootEnabled());
    EXPECT_TRUE(bios.ValidateBootConfig());

    bios.SetBootMode("Legacy");
    EXPECT_THROW(bios.ValidateBootConfig(), POSTFailureException);

    bios.ToggleSecureBoot(false);
    EXPECT_TRUE(bios.ValidateBootConfig());

    EXPECT_THROW(bios.SetBootMode("InvalidMode"), ComputerException);
}

TEST(BIOSSettingsTest, EqualityAndStream) {
    BIOSSettings b1("UEFI", true, true, false);
    BIOSSettings b2("UEFI", true, true, false);
    BIOSSettings b3("Legacy", false, false, true);

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
    EXPECT_TRUE(b1 != b3);

    std::ostringstream oss;
    oss << b1;
    EXPECT_NE(oss.str().find("UEFI"), std::string::npos);
}