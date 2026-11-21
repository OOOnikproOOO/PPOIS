/**
 * @file test_thermal_paste.cpp
 * @brief Unit tests for the ThermalPaste class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "ThermalPaste.h"

TEST(ThermalPasteTest, ConstructorAndGetters) {
    ThermalPaste paste("Noctua NT-H1", 8.9, 50000.0, 0.04);
    EXPECT_EQ(paste.GetBrandName(), "Noctua NT-H1");
    EXPECT_DOUBLE_EQ(paste.GetThermalConductivity(), 8.9);
    EXPECT_DOUBLE_EQ(paste.GetViscosity(), 50000.0);
    EXPECT_DOUBLE_EQ(paste.GetThicknessMm(), 0.04);
    EXPECT_DOUBLE_EQ(paste.GetServiceYears(), 0.0);
    EXPECT_FALSE(paste.IsDry());
    EXPECT_TRUE(paste.IsEffective());
}

TEST(ThermalPasteTest, ThermalResistanceCalculation) {
    ThermalPaste paste("Generic", 10.0, 40000.0, 0.1);
    EXPECT_DOUBLE_EQ(paste.CalculateThermalResistance(0.0), 1.0);
    EXPECT_GT(paste.CalculateThermalResistance(4.0), 0.0);
}

TEST(ThermalPasteTest, DegradationAndReplacement) {
    ThermalPaste paste("Thermal Grizzly", 12.5, 40000.0, 0.03);
    EXPECT_DOUBLE_EQ(paste.EvaluateHeatTransferEfficiency(), 1.0);

    paste.DegradeOverTime(0.0);
    EXPECT_DOUBLE_EQ(paste.GetServiceYears(), 0.0);

    paste.DegradeOverTime(3.5);
    EXPECT_TRUE(paste.IsDry());
    EXPECT_LT(paste.GetThermalConductivity(), 12.5);
    EXPECT_FALSE(paste.IsEffective());
    EXPECT_DOUBLE_EQ(paste.EvaluateHeatTransferEfficiency(), 0.2);

    paste.ReplacePaste(14.0, 0.02);
    EXPECT_FALSE(paste.IsDry());
    EXPECT_DOUBLE_EQ(paste.GetServiceYears(), 0.0);
    EXPECT_DOUBLE_EQ(paste.GetThermalConductivity(), 14.0);
    EXPECT_TRUE(paste.IsEffective());
}

TEST(ThermalPasteTest, EqualityAndStream) {
    ThermalPaste p1("Arctic MX-4", 8.5, 45000.0, 0.05);
    ThermalPaste p2("Arctic MX-4", 8.5, 45000.0, 0.05);
    ThermalPaste p3("Noctua", 8.9, 50000.0, 0.04);

    EXPECT_TRUE(p1 == p2);
    EXPECT_TRUE(p1 != p3);

    std::stringstream ss;
    ss << p1;
    EXPECT_NE(ss.str().find("Thermal Paste: Arctic MX-4"), std::string::npos);
}