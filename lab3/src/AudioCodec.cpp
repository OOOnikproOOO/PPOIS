/**
 * @file AudioCodec.cpp
 * @brief Implementation of AudioCodec methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioCodec.h"
#include "UnsupportedAudioFormatException.h"

AudioCodec::AudioCodec(const std::string& codec_name, int bitrate_kbps, int sample_rate_hz, int channels_count, bool is_lossless) :
    codec_name_(codec_name), bitrate_kbps_(bitrate_kbps), sample_rate_hz_(sample_rate_hz), channels_count_(channels_count), is_lossless_(is_lossless) {}

bool AudioCodec::operator==(const AudioCodec& other) const {
    return codec_name_ == other.codec_name_ &&
           bitrate_kbps_ == other.bitrate_kbps_ &&
           sample_rate_hz_ == other.sample_rate_hz_ &&
           channels_count_ == other.channels_count_ &&
           is_lossless_ == other.is_lossless_;
}

bool AudioCodec::operator!=(const AudioCodec& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioCodec& codec) {
    os << codec.codec_name_ << " [" << codec.bitrate_kbps_ << " kbps, " << codec.sample_rate_hz_ << " Hz, " << (codec.is_lossless_ ? "Lossless" : "Lossy") << "]";
    return os;
}

size_t AudioCodec::CalculateBytesPerSecond() const {
    const size_t kBitsPerByte = 8;
    return static_cast<size_t>((bitrate_kbps_ * 1000) / kBitsPerByte);
}

double AudioCodec::EstimateFileSizeMb(double duration_sec) const {
    if (duration_sec <= 0.0)
        return 0.0;
    
    const double kBytesPerMb = 1024.0 * 1024.0;
    return (CalculateBytesPerSecond() * duration_sec) / kBytesPerMb;
}

void AudioCodec::ValidateParameters() const {
    const int kMinSampleRate = 8000;
    const int kMaxSampleRate = 192000;
    if (sample_rate_hz_ < kMinSampleRate || sample_rate_hz_ > kMaxSampleRate)
        throw UnsupportedAudioFormatException("Unsupported sample rate: " + std::to_string(sample_rate_hz_) + " Hz");
    
    if (channels_count_ < 1 || channels_count_ > 8)
        throw UnsupportedAudioFormatException("Unsupported channel count: " + std::to_string(channels_count_));
}

void AudioCodec::SetBitrate(int bitrate) {
    const int kMinBitrate = 32;
    const int kMaxBitrate = 9216;
    if (bitrate >= kMinBitrate && bitrate <= kMaxBitrate)
        bitrate_kbps_ = bitrate;
}

const std::string& AudioCodec::GetCodecName() const {
    return codec_name_;
}

int AudioCodec::GetBitrateKbps() const {
    return bitrate_kbps_;
}

int AudioCodec::GetSampleRateHz() const {
    return sample_rate_hz_;
}

int AudioCodec::GetChannelsCount() const {
    return channels_count_;
}

bool AudioCodec::IsLossless() const {
    return is_lossless_;
}