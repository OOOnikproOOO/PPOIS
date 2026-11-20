/**
 * @file test_online_radio_station.cpp
 * @brief Unit tests for OnlineRadioStation class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "OnlineRadioStation.h"
#include "StreamingNetworkException.h"

TEST(OnlineRadioStationTest, ConstructorAndGetters) {
    OnlineRadioStation station("Synthwave FM", "http://synthwave.fm:8000/stream", "Synthwave", 320, true);
    EXPECT_EQ(station.GetStationName(), "Synthwave FM");
    EXPECT_EQ(station.GetStreamUrl(), "http://synthwave.fm:8000/stream");
    EXPECT_EQ(station.GetGenre(), "Synthwave");
    EXPECT_EQ(station.GetBitrateKbps(), 320);
    EXPECT_TRUE(station.IsOnline());
}

TEST(OnlineRadioStationTest, ConnectAndDisconnect) {
    OnlineRadioStation station("Jazz Lounge", "http://jazz.fm/live", "Jazz", 192, false);
    EXPECT_FALSE(station.IsOnline());

    station.Connect();
    EXPECT_TRUE(station.IsOnline());

    station.Disconnect();
    EXPECT_FALSE(station.IsOnline());

    station.SetStreamUrl("invalid-url");
    EXPECT_THROW(station.Connect(), StreamingNetworkException);
}

TEST(OnlineRadioStationTest, FormattingAndBitrateClamping) {
    OnlineRadioStation station("Low", "http://stream.org", "Talk", 10, true);
    EXPECT_EQ(station.GetBitrateKbps(), 32);

    std::string info = station.FormatStationInfo();
    EXPECT_NE(info.find("Low"), std::string::npos);
    EXPECT_NE(info.find("ONLINE"), std::string::npos);
}

TEST(OnlineRadioStationTest, EqualityAndStream) {
    OnlineRadioStation s1("Radio 1", "http://r1.com", "Pop");
    OnlineRadioStation s2("Radio 1", "http://r1.com", "Pop");
    OnlineRadioStation s3("Radio 2", "http://r2.com", "Rock");

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}