/**
 * @file AudioEngine.cpp
 * @brief Implementation of AudioEngine methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioEngine.h"
#include "PlaybackBufferUnderflowException.h"

AudioEngine::AudioEngine(int sample_rate_hz, size_t buffer_capacity) :
    state_("Stopped"), sample_rate_hz_(sample_rate_hz > 0 ? sample_rate_hz : 44100), buffer_underruns_count_(0), playback_buffer_(buffer_capacity) {}

bool AudioEngine::operator==(const AudioEngine& other) const {
    return state_ == other.state_ &&
           sample_rate_hz_ == other.sample_rate_hz_ &&
           buffer_underruns_count_ == other.buffer_underruns_count_ &&
           playback_buffer_ == other.playback_buffer_;
}

bool AudioEngine::operator!=(const AudioEngine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioEngine& engine) {
    os << "AudioEngine[" << engine.state_ << ", " << engine.sample_rate_hz_ << " Hz, Underruns: " << engine.buffer_underruns_count_ << "]";
    return os;
}

void AudioEngine::Play() {
    state_ = "Playing";
}

void AudioEngine::Pause() {
    if (state_ == "Playing")
        state_ = "Paused";
}

void AudioEngine::Stop() {
    state_ = "Stopped";
    playback_buffer_.Clear();
}

size_t AudioEngine::RenderAudioBuffer(size_t samples_to_render) {
    if (state_ != "Playing")
        return 0;
    
    size_t rendered = 0;
    for (size_t i = 0; i < samples_to_render; i++) {
        try {
            playback_buffer_.ReadSample();
            rendered++;
        } catch (const PlaybackBufferUnderflowException&) {
            buffer_underruns_count_++;
            break;
        }
    }
    return rendered;
}

void AudioEngine::ResetEngine() {
    state_ = "Stopped";
    buffer_underruns_count_ = 0;
    playback_buffer_.Clear();
}

const std::string& AudioEngine::GetState() const {
    return state_;
}

int AudioEngine::GetSampleRateHz() const {
    return sample_rate_hz_;
}

int AudioEngine::GetBufferUnderrunsCount() const {
    return buffer_underruns_count_;
}

AudioBuffer& AudioEngine::GetBuffer() {
    return playback_buffer_;
}

const AudioBuffer& AudioEngine::GetBuffer() const {
    return playback_buffer_;
}