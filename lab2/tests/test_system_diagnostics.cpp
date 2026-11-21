#include <gtest/gtest.h>
#include <sstream>
#include "SystemDiagnostics.h"
#include "ThermalThrottlingException.h"
#include "PowerSupplyOverloadException.h"

TEST(SystemDiagnosticsTest, ConstructorAndGetters) {
    SystemDiagnostics diag(true, 0, 40.0, 350.0);
    EXPECT_TRUE(diag.IsNominal());
    EXPECT_EQ(diag.GetWarningsCount(), 0);
    EXPECT_DOUBLE_EQ(diag.GetMaxRecordedTemp(), 40.0);
    EXPECT_DOUBLE_EQ(diag.GetTotalPowerDraw(), 350.0);
}

TEST(SystemDiagnosticsTest, TemperatureAndPowerDiagnostics) {
    SystemDiagnostics diag;
    EXPECT_TRUE(diag.DiagnoseTemperatures(65.0, 72.0, 55.0));
    EXPECT_DOUBLE_EQ(diag.GetMaxRecordedTemp(), 72.0);

    EXPECT_THROW(diag.DiagnoseTemperatures(100.0, 70.0, 50.0), ThermalThrottlingException);
    EXPECT_FALSE(diag.IsNominal());
    EXPECT_EQ(diag.GetWarningsCount(), 1);

    EXPECT_TRUE(diag.DiagnosePower(400, 850));
    EXPECT_THROW(diag.DiagnosePower(900, 850), PowerSupplyOverloadException);
    EXPECT_EQ(diag.GetWarningsCount(), 2);

    diag.RecordIncident();
    EXPECT_EQ(diag.GetWarningsCount(), 3);

    diag.ResetDiagnostics();
    EXPECT_TRUE(diag.IsNominal());
    EXPECT_EQ(diag.GetWarningsCount(), 0);
}

TEST(SystemDiagnosticsTest, EqualityAndStream) {
    SystemDiagnostics d1(true, 0, 30.0, 100.0);
    SystemDiagnostics d2(true, 0, 30.0, 100.0);
    SystemDiagnostics d3(false, 3, 98.0, 800.0);

    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_TRUE(d1 != d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_NE(oss.str().find("NOMINAL"), std::string::npos);
}