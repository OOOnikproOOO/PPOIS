/**
 * @file AudioTrack.h
 * @brief Declaration of the AudioTrack class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOTRACK_H
#define AUDIOTRACK_H

#include <iostream>
#include <string>
#include "AudioMetadata.h"
#include "AudioCodec.h"

/**
 * @brief Represents a playable audio track combining file references, metadata, and codec specs.
 */
class AudioTrack {
public:
    /**
     * @brief Constructs an AudioTrack.
     * @param file_path Filesystem path to audio file.
     * @param duration_sec Length of track in seconds.
     * @param metadata Descriptive metadata.
     * @param codec Audio encoding specifications.
     */
    AudioTrack(const std::string& file_path = "music/track.mp3", double duration_sec = 215.0, const AudioMetadata& metadata = AudioMetadata(), const AudioCodec& codec = AudioCodec());

    bool operator==(const AudioTrack& other) const;
    bool operator!=(const AudioTrack& other) const;
    friend std::ostream& operator<<(std::ostream& os, const AudioTrack& track);

    /**
     * @brief Simulates playback, incrementing total play counter.
     */
    void Play();

    /**
     * @brief Toggles favorite bookmark status.
     */
    void ToggleFavorite();

    /**
     * @brief Updates internal metadata object.
     * @param new_meta Replacement metadata.
     */
    void UpdateMetadata(const AudioMetadata& new_meta);

    /**
     * @brief Formats track duration as 'MM:SS'.
     * @return Formatted timestamp string.
     */
    std::string FormatDurationString() const;

    const std::string& GetFilePath() const;
    double GetDurationSec() const;
    int GetPlayCount() const;
    bool IsFavorite() const;
    const AudioMetadata& GetMetadata() const;
    const AudioCodec& GetCodec() const;

private:
    std::string file_path_;
    double duration_sec_;
    int play_count_;
    bool is_favorite_;
    AudioMetadata metadata_;
    AudioCodec codec_;
};

#endif