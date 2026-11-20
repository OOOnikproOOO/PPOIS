/**
 * @file test_plugin_manager.cpp
 * @brief Unit tests for PluginManager class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PluginManager.h"

TEST(PluginManagerTest, ConstructorAndGetters) {
    PluginManager pm(2, true);
    EXPECT_EQ(pm.GetApiVersion(), 2);
    EXPECT_TRUE(pm.IsAllowUnsigned());
    EXPECT_EQ(pm.GetExtensionsCount(), 0u);
}

TEST(PluginManagerTest, InstallUninstallAndQuery) {
    PluginManager pm;
    EXPECT_TRUE(pm.InstallExtension("DSP_Reverb_Pro"));
    EXPECT_TRUE(pm.InstallExtension("Spectrum_Visualizer"));
    EXPECT_FALSE(pm.InstallExtension("DSP_Reverb_Pro"));
    EXPECT_FALSE(pm.InstallExtension(""));

    EXPECT_EQ(pm.GetExtensionsCount(), 2u);
    EXPECT_TRUE(pm.HasExtension("DSP_Reverb_Pro"));
    EXPECT_FALSE(pm.HasExtension("Nonexistent"));

    EXPECT_TRUE(pm.UninstallExtension("DSP_Reverb_Pro"));
    EXPECT_FALSE(pm.HasExtension("DSP_Reverb_Pro"));
    EXPECT_FALSE(pm.UninstallExtension("DSP_Reverb_Pro"));

    pm.ClearExtensions();
    EXPECT_EQ(pm.GetExtensionsCount(), 0u);
}

TEST(PluginManagerTest, EqualityAndStream) {
    PluginManager m1(1, false);
    PluginManager m2(1, false);
    PluginManager m3(2, false);

    EXPECT_EQ(m1, m2);
    EXPECT_NE(m1, m3);

    std::ostringstream oss;
    oss << m1;
    EXPECT_FALSE(oss.str().empty());
}