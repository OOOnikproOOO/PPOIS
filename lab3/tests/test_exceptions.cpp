/**
 * @file test_exceptions.cpp
 * @brief Unit tests for domain exceptions of Music Player.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include "MusicPlayerException.h"
#include "TrackNotFoundException.h"
#include "PlaylistNotFoundException.h"
#include "CorruptedAudioFileException.h"
#include "UnsupportedAudioFormatException.h"
#include "DeviceAudioOutputException.h"
#include "PlaybackBufferUnderflowException.h"
#include "InvalidEqualizerBandException.h"
#include "PlaylistFullException.h"
#include "UnauthorizedPlaybackException.h"
#include "StreamingNetworkException.h"
#include "LicenseExpiredException.h"

TEST(ExceptionsTest, BaseExceptionMessage) {
    try {
        throw MusicPlayerException("Base error");
    } catch (const MusicPlayerException& e) {
        EXPECT_STREQ(e.what(), "Base error");
    }
}

TEST(ExceptionsTest, DerivedExceptionsInheritance) {
    EXPECT_THROW(throw TrackNotFoundException("Track missing"), MusicPlayerException);
    EXPECT_THROW(throw PlaylistNotFoundException("Playlist missing"), MusicPlayerException);
    EXPECT_THROW(throw CorruptedAudioFileException("CRC mismatch"), MusicPlayerException);
    EXPECT_THROW(throw UnsupportedAudioFormatException("Unknown format"), MusicPlayerException);
    EXPECT_THROW(throw DeviceAudioOutputException("Audio device lost"), MusicPlayerException);
    EXPECT_THROW(throw PlaybackBufferUnderflowException("Buffer drained"), MusicPlayerException);
    EXPECT_THROW(throw InvalidEqualizerBandException("Invalid frequency"), MusicPlayerException);
    EXPECT_THROW(throw PlaylistFullException("Playlist at capacity"), MusicPlayerException);
    EXPECT_THROW(throw UnauthorizedPlaybackException("Premium required"), MusicPlayerException);
    EXPECT_THROW(throw StreamingNetworkException("Timeout"), MusicPlayerException);
    EXPECT_THROW(throw LicenseExpiredException("DRM expired"), MusicPlayerException);
}