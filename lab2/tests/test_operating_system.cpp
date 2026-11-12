#include <gtest/gtest.h>
#include <sstream>
#include "OperatingSystem.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"
#include "POSTFailureException.h"

TEST(OperatingSystemTest, BootShutdownDriversAndUptime) {
    OperatingSystem os("Ubuntu Linux 24.04 LTS");
    os.RegisterDriver(DeviceDriver("nvidia-drm", "550.54", "GPU", false));
    os.RegisterDriver(DeviceDriver("nvme-core", "2.4.0", "Storage", false));

    EXPECT_EQ(os.GetOsName(), "Ubuntu Linux 24.04 LTS");
    EXPECT_FALSE(os.IsBooted());
    EXPECT_EQ(os.GetDriverCount(), 2);
    EXPECT_THROW(os.AdvanceUptime(10), ComputerException);
    EXPECT_THROW(os.RegisterDriver(DeviceDriver("")), ComputerException);
    EXPECT_THROW(os.GetDriver(5), DeviceNotFoundException);

    os.Boot();
    EXPECT_TRUE(os.IsBooted());
    EXPECT_TRUE(os.GetBootloader().IsVerified());
    EXPECT_TRUE(os.GetDriver(0).IsLoaded());
    EXPECT_TRUE(os.GetDriver(1).IsLoaded());

    os.AdvanceUptime(65);
    EXPECT_EQ(os.GetClock().GetUptimeSeconds(), 65);
    EXPECT_EQ(os.GetClock().FormatUptime(), "00:01:05");

    os.GetFileSystem().CreateFile("/", "hello.txt", "World");
    EXPECT_EQ(os.GetFileSystem().ReadFile("/", "hello.txt"), "World");

    os.GetScheduler().LaunchProcess(OSProcess(1, "systemd", 64, true));
    EXPECT_EQ(os.GetScheduler().GetProcessCount(), 1);

    os.Shutdown();
    EXPECT_FALSE(os.IsBooted());
    EXPECT_FALSE(os.GetDriver(0).IsLoaded());
}

TEST(OperatingSystemTest, BootFailureOnInvalidBios) {
    OperatingSystem os;
    os.GetBootloader().GetBiosSettings().SetBootMode("Legacy");
    EXPECT_THROW(os.Boot(), POSTFailureException);
    EXPECT_FALSE(os.IsBooted());
}

TEST(OperatingSystemTest, EqualityAndStream) {
    OperatingSystem os1("Debian 12");
    OperatingSystem os2("Debian 12");
    OperatingSystem os3("Windows 11");

    EXPECT_TRUE(os1 == os2);
    EXPECT_FALSE(os1 == os3);
    EXPECT_TRUE(os1 != os3);

    std::ostringstream oss;
    oss << os1;
    EXPECT_NE(oss.str().find("Debian 12"), std::string::npos);
}