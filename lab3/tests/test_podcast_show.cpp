/**
 * @file test_podcast_show.cpp
 * @brief Unit tests for PodcastShow class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PodcastShow.h"
#include "TrackNotFoundException.h"

TEST(PodcastShowTest, ConstructorAndGetters) {
    PodcastShow show("Hardcore History", "Dan Carlin", "History");
    EXPECT_EQ(show.GetShowTitle(), "Hardcore History");
    EXPECT_EQ(show.GetHostName(), "Dan Carlin");
    EXPECT_EQ(show.GetCategory(), "History");
    EXPECT_EQ(show.GetEpisodes().size(), 0u);
}

TEST(PodcastShowTest, AddAndFindEpisodes) {
    PodcastShow show;
    PodcastEpisode ep1("Intro", 1, 1200.0, "2026.01.01", true);
    PodcastEpisode ep2("Main", 2, 3600.0, "2026.01.08", false);

    show.AddEpisode(ep1);
    show.AddEpisode(ep2);

    EXPECT_EQ(show.GetEpisodes().size(), 2u);
    EXPECT_EQ(show.GetUnlistenedCount(), 1u);
    EXPECT_DOUBLE_EQ(show.CalculateTotalDurationSec(), 4800.0);

    const PodcastEpisode& found = show.FindEpisode(2);
    EXPECT_EQ(found.GetTitle(), "Main");

    EXPECT_THROW(show.FindEpisode(99), TrackNotFoundException);
}

TEST(PodcastShowTest, EqualityAndStream) {
    PodcastShow s1("Show 1", "Host");
    PodcastShow s2("Show 1", "Host");
    PodcastShow s3("Show 2", "Host");

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}