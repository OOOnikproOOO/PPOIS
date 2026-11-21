#include <gtest/gtest.h>
#include <sstream>
#include "DeviceDriver.h"
#include "ComputerException.h"

TEST(DeviceDriverTest, ConstructorAndGetters) {
    DeviceDriver drv("nvidia-drm", "550.54", "GPU", false);
    EXPECT_EQ(drv.GetDriverName(), "nvidia-drm");
    EXPECT_EQ(drv.GetVersion(), "550.54");
    EXPECT_EQ(drv.GetDeviceType(), "GPU");
    EXPECT_FALSE(drv.IsLoaded());
}

TEST(DeviceDriverTest, LoadUnloadAndUpdate) {
    DeviceDriver drv("snd_hda_intel", "1.0.2", "Audio", false);
    drv.Load();
    EXPECT_TRUE(drv.IsLoaded());

    drv.UpdateVersion("1.1.0");
    EXPECT_EQ(drv.GetVersion(), "1.1.0");
    EXPECT_THROW(drv.UpdateVersion(""), ComputerException);

    drv.Unload();
    EXPECT_FALSE(drv.IsLoaded());
}

TEST(DeviceDriverTest, EqualityAndStream) {
    DeviceDriver d1("nvme", "2.1", "Storage", true);
    DeviceDriver d2("nvme", "2.1", "Storage", true);
    DeviceDriver d3("e1000e", "3.8", "Network", false);

    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_TRUE(d1 != d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_NE(oss.str().find("nvme"), std::string::npos);
}