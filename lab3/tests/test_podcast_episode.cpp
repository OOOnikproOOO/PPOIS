/**
 * @file test_podcast_episode.cpp
 * @brief Unit tests for PodcastEpisode class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PodcastEpisode.h"

TEST(PodcastEpisodeTest, ConstructorAndGetters) {
    PodcastEpisode ep("Deep Dive AI", 42, 5400.0, "2026.11.15", false);
    EXPECT_EQ(ep.GetTitle(), "Deep Dive AI");
    EXPECT_EQ(ep.GetEpisodeNumber(), 42);
    EXPECT_DOUBLE_EQ(ep.GetDurationSec(), 5400.0);
    EXPECT_EQ(ep.GetReleaseDate(), "2026.11.15");
    EXPECT_FALSE(ep.IsListened());
}

TEST(PodcastEpisodeTest, MarkListenedAndSummary) {
    PodcastEpisode ep("Tech Talk", 1, 1800.0);
    EXPECT_FALSE(ep.IsListened());

    ep.MarkAsListened(true);
    EXPECT_TRUE(ep.IsListened());

    std::string summary = ep.FormatEpisodeSummary();
    EXPECT_NE(summary.find("#1"), std::string::npos);
    EXPECT_NE(summary.find("Tech Talk"), std::string::npos);
    EXPECT_NE(summary.find("[Listened]"), std::string::npos);

    ep.UpdateDuration(2400.0);
    EXPECT_DOUBLE_EQ(ep.GetDurationSec(), 2400.0);
}

TEST(PodcastEpisodeTest, EqualityAndStream) {
    PodcastEpisode e1("Ep 1", 1, 1000.0, "2026.01.01");
    PodcastEpisode e2("Ep 1", 1, 1000.0, "2026.01.01");
    PodcastEpisode e3("Ep 2", 2, 1000.0, "2026.01.01");

    EXPECT_EQ(e1, e2);
    EXPECT_NE(e1, e3);

    std::ostringstream oss;
    oss << e1;
    EXPECT_FALSE(oss.str().empty());
}