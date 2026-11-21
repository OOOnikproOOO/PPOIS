/**
 * @file test_playback_queue.cpp
 * @brief Unit tests for PlaybackQueue class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PlaybackQueue.h"
#include "TrackNotFoundException.h"

TEST(PlaybackQueueTest, ConstructorAndGetters) {
    PlaybackQueue queue(100, true);
    EXPECT_EQ(queue.GetQueueSize(), 0u);
    EXPECT_EQ(queue.GetCurrentIndex(), -1);
    EXPECT_TRUE(queue.IsAutoAdvance());
}

TEST(PlaybackQueueTest, EnqueueAndNavigation) {
    PlaybackQueue queue(3);
    AudioTrack t1("song1.mp3", 100.0, AudioMetadata("Track 1"));
    AudioTrack t2("song2.mp3", 150.0, AudioMetadata("Track 2"));

    EXPECT_TRUE(queue.Enqueue(t1));
    EXPECT_TRUE(queue.Enqueue(t2));
    EXPECT_EQ(queue.GetQueueSize(), 2u);
    EXPECT_EQ(queue.GetCurrentIndex(), 0);

    EXPECT_EQ(queue.GetCurrentTrack().GetMetadata().GetTitle(), "Track 1");

    EXPECT_TRUE(queue.NextTrack());
    EXPECT_EQ(queue.GetCurrentIndex(), 1);
    EXPECT_EQ(queue.GetCurrentTrack().GetMetadata().GetTitle(), "Track 2");

    EXPECT_FALSE(queue.NextTrack());
    EXPECT_TRUE(queue.PreviousTrack());
    EXPECT_EQ(queue.GetCurrentIndex(), 0);
    EXPECT_FALSE(queue.PreviousTrack());
}

TEST(PlaybackQueueTest, RemoveAndExceptions) {
    PlaybackQueue queue(5);
    EXPECT_THROW(queue.GetCurrentTrack(), TrackNotFoundException);

    queue.Enqueue(AudioTrack("t1.mp3"));
    queue.Enqueue(AudioTrack("t2.mp3"));
    queue.RemoveAt(0);
    EXPECT_EQ(queue.GetQueueSize(), 1u);

    queue.ClearQueue();
    EXPECT_EQ(queue.GetQueueSize(), 0u);
    EXPECT_EQ(queue.GetCurrentIndex(), -1);
}

TEST(PlaybackQueueTest, EqualityAndStream) {
    PlaybackQueue q1(10);
    PlaybackQueue q2(10);
    PlaybackQueue q3(20);

    EXPECT_EQ(q1, q2);
    EXPECT_NE(q1, q3);

    std::ostringstream oss;
    oss << q1;
    EXPECT_FALSE(oss.str().empty());
}