/**
 * @file AudioStream.cpp
 * @brief Implementation of AudioStream methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioStream.h"
#include <cmath>

AudioStream::AudioStream(const std::string& stream_source, double total_duration_sec, size_t buffer_capacity) :
    stream_source_(stream_source), total_duration_sec_(total_duration_sec > 0.0 ? total_duration_sec : 1.0), current_position_sec_(0.0), is_eof_(false), buffer_(buffer_capacity) {}

bool AudioStream::operator==(const AudioStream& other) const {
    const double kEpsilon = 1e-4;
    return stream_source_ == other.stream_source_ &&
           std::abs(total_duration_sec_ - other.total_duration_sec_) < kEpsilon &&
           std::abs(current_position_sec_ - other.current_position_sec_) < kEpsilon &&
           is_eof_ == other.is_eof_ &&
           buffer_ == other.buffer_;
}

bool AudioStream::operator!=(const AudioStream& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioStream& stream) {
    os << "AudioStream[" << stream.stream_source_ << " (" << stream.current_position_sec_ << "/" << stream.total_duration_sec_ << "s)]";
    return os;
}

size_t AudioStream::ReadNextChunk(size_t samples_count) {
    if (is_eof_)
        return 0;
    
    size_t pushed = 0;
    for (size_t i = 0; i < samples_count; ++i) {
        if (!buffer_.WriteSample(AudioSample(0.1, 0.1, 16)))
            break;
        ++pushed;
    }
    const double kSecondsPerChunk = 0.05;
    current_position_sec_ += kSecondsPerChunk;
    if (current_position_sec_ >= total_duration_sec_) {
        current_position_sec_ = total_duration_sec_;
        is_eof_ = true;
    }
    return pushed;
}

void AudioStream::Seek(double position_sec) {
    if (position_sec < 0.0) {
        current_position_sec_ = 0.0;
    } else if (position_sec > total_duration_sec_) {
        current_position_sec_ = total_duration_sec_;
        is_eof_ = true;
    } else {
        current_position_sec_ = position_sec;
        is_eof_ = false;
    }
    buffer_.Clear();
}

void AudioStream::ResetStream() {
    current_position_sec_ = 0.0;
    is_eof_ = false;
    buffer_.Clear();
}

double AudioStream::GetRemainingTimeSec() const {
    double remaining = total_duration_sec_ - current_position_sec_;
    return remaining > 0.0 ? remaining : 0.0;
}

const std::string& AudioStream::GetStreamSource() const {
    return stream_source_;
}

double AudioStream::GetTotalDurationSec() const {
    return total_duration_sec_;
}

double AudioStream::GetCurrentPositionSec() const {
    return current_position_sec_;
}

bool AudioStream::IsEof() const {
    return is_eof_;
}

const AudioBuffer& AudioStream::GetBuffer() const {
    return buffer_;
}