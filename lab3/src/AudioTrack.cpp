/**
 * @file AudioTrack.cpp
 * @brief Implementation of AudioTrack methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioTrack.h"
#include <iomanip>
#include <sstream>

AudioTrack::AudioTrack(const std::string& file_path, double duration_sec, const AudioMetadata& metadata, const AudioCodec& codec) :
    file_path_(file_path), duration_sec_(duration_sec > 0.0 ? duration_sec : 1.0), play_count_(0), is_favorite_(false), metadata_(metadata), codec_(codec) {}

bool AudioTrack::operator==(const AudioTrack& other) const {
    const double kEpsilon = 1e-4;
    return file_path_ == other.file_path_ &&
           std::abs(duration_sec_ - other.duration_sec_) < kEpsilon &&
           play_count_ == other.play_count_ &&
           is_favorite_ == other.is_favorite_ &&
           metadata_ == other.metadata_ &&
           codec_ == other.codec_;
}

bool AudioTrack::operator!=(const AudioTrack& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioTrack& track) {
    os << track.metadata_ << " [" << track.FormatDurationString() << ", Plays: " << track.play_count_ << (track.is_favorite_ ? ", ★" : "") << "]";
    return os;
}

void AudioTrack::Play() {
    play_count_++;
}

void AudioTrack::ToggleFavorite() {
    is_favorite_ = !is_favorite_;
}

void AudioTrack::UpdateMetadata(const AudioMetadata& new_meta) {
    metadata_ = new_meta;
}

std::string AudioTrack::FormatDurationString() const {
    int total_sec = static_cast<int>(duration_sec_);
    int minutes = total_sec / 60;
    int seconds = total_sec % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
    return oss.str();
}

const std::string& AudioTrack::GetFilePath() const {
    return file_path_;
}

double AudioTrack::GetDurationSec() const {
    return duration_sec_;
}

int AudioTrack::GetPlayCount() const {
    return play_count_;
}

bool AudioTrack::IsFavorite() const {
    return is_favorite_;
}

const AudioMetadata& AudioTrack::GetMetadata() const {
    return metadata_;
}

const AudioCodec& AudioTrack::GetCodec() const {
    return codec_;
}