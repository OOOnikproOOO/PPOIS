/**
 * @file test_stream_downloader.cpp
 * @brief Unit tests for StreamDownloader class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "StreamDownloader.h"

TEST(StreamDownloaderTest, ConstructorAndGetters) {
    StreamDownloader dl("http://stream.com/track.flac", 2048000, false);
    EXPECT_EQ(dl.GetDownloadUrl(), "http://stream.com/track.flac");
    EXPECT_EQ(dl.GetTotalBytes(), 2048000u);
    EXPECT_EQ(dl.GetBytesDownloaded(), 0u);
    EXPECT_FALSE(dl.IsCompleted());
    EXPECT_DOUBLE_EQ(dl.CalculateProgressPercentage(), 0.0);
}

TEST(StreamDownloaderTest, ProcessChunkAndSpeed) {
    StreamDownloader dl("http://cdn.com/song.mp3", 10240, false);
    dl.ProcessChunk(5120, 1.0);
    EXPECT_EQ(dl.GetBytesDownloaded(), 5120u);
    EXPECT_DOUBLE_EQ(dl.CalculateProgressPercentage(), 50.0);
    EXPECT_DOUBLE_EQ(dl.GetDownloadSpeedKbps(), 5.0);
    EXPECT_FALSE(dl.IsCompleted());

    dl.ProcessChunk(6000, 1.0);
    EXPECT_EQ(dl.GetBytesDownloaded(), 10240u);
    EXPECT_DOUBLE_EQ(dl.CalculateProgressPercentage(), 100.0);
    EXPECT_TRUE(dl.IsCompleted());

    dl.Cancel();
    EXPECT_EQ(dl.GetBytesDownloaded(), 0u);
    EXPECT_FALSE(dl.IsCompleted());
}

TEST(StreamDownloaderTest, ZeroTotalBytesAndSetUrl) {
    StreamDownloader dl("http://old.com", 0);
    EXPECT_DOUBLE_EQ(dl.CalculateProgressPercentage(), 0.0);

    dl.SetUrl("http://new.com");
    EXPECT_EQ(dl.GetDownloadUrl(), "http://new.com");
}

TEST(StreamDownloaderTest, EqualityAndStream) {
    StreamDownloader d1("http://url", 1000);
    StreamDownloader d2("http://url", 1000);
    StreamDownloader d3("http://other", 1000);

    EXPECT_EQ(d1, d2);
    EXPECT_NE(d1, d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_FALSE(oss.str().empty());
}