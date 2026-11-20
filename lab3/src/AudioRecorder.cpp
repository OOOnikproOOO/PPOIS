/**
 * @file AudioRecorder.cpp
 * @brief Implementation of AudioRecorder methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioRecorder.h"
#include <iomanip>
#include <sstream>
#include <cmath>

AudioRecorder::AudioRecorder(int sample_rate_hz, size_t buffer_capacity, bool is_recording) :
    sample_rate_hz_(sample_rate_hz < 8000 ? 8000 : (sample_rate_hz > 192000 ? 192000 : sample_rate_hz)), recorded_seconds_(0.0), is_recording_(is_recording), recorded_buffer_(buffer_capacity) {}

bool AudioRecorder::operator==(const AudioRecorder& other) const {
    const double kEpsilon = 1e-4;
    return sample_rate_hz_ == other.sample_rate_hz_ &&
           std::abs(recorded_seconds_ - other.recorded_seconds_) < kEpsilon &&
           is_recording_ == other.is_recording_;
}

bool AudioRecorder::operator!=(const AudioRecorder& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioRecorder& rec) {
    os << "AudioRecorder[" << (rec.is_recording_ ? "RECORDING" : "STOPPED") << ", Duration: " << std::fixed << std::setprecision(2) << rec.recorded_seconds_ << "s, " << rec.sample_rate_hz_ << " Hz]";
    return os;
}

void AudioRecorder::StartRecording() {
    is_recording_ = true;
}

void AudioRecorder::StopRecording() {
    is_recording_ = false;
}

bool AudioRecorder::CaptureSample(const AudioSample& sample) {
    if (!is_recording_)
        return false;

    bool written = recorded_buffer_.WriteSample(sample);
    if (written && sample_rate_hz_ > 0)
        recorded_seconds_ += 1.0 / sample_rate_hz_;

    return written;
}

void AudioRecorder::Reset() {
    recorded_buffer_.Clear();
    recorded_seconds_ = 0.0;
    is_recording_ = false;
}

int AudioRecorder::GetSampleRateHz() const {
    return sample_rate_hz_;
}

double AudioRecorder::GetRecordedSeconds() const {
    return recorded_seconds_;
}

bool AudioRecorder::IsRecording() const {
    return is_recording_;
}

const AudioBuffer& AudioRecorder::GetBuffer() const {
    return recorded_buffer_;
}