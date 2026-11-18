/**
 * @file AudioBuffer.cpp
 * @brief Implementation of AudioBuffer methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioBuffer.h"
#include "PlaybackBufferUnderflowException.h"

AudioBuffer::AudioBuffer(size_t capacity_samples) :
    samples_(capacity_samples > 0 ? capacity_samples : 1024), capacity_samples_(capacity_samples > 0 ? capacity_samples : 1024), read_index_(0), write_index_(0), count_(0), is_underrun_(false) {}

bool AudioBuffer::operator==(const AudioBuffer& other) const {
    return capacity_samples_ == other.capacity_samples_ &&
           count_ == other.count_ &&
           is_underrun_ == other.is_underrun_;
}

bool AudioBuffer::operator!=(const AudioBuffer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioBuffer& buffer) {
    os << "AudioBuffer[" << buffer.count_ << "/" << buffer.capacity_samples_ << " samples]";
    return os;
}

bool AudioBuffer::WriteSample(const AudioSample& sample) {
    if (count_ >= capacity_samples_)
        return false;
    
    samples_[write_index_] = sample;
    write_index_ = (write_index_ + 1) % capacity_samples_;
    count_++;
    is_underrun_ = false;
    return true;
}

AudioSample AudioBuffer::ReadSample() {
    if (count_ == 0) {
        is_underrun_ = true;
        throw PlaybackBufferUnderflowException("Audio buffer underflow: attempted read from empty buffer.");
    }
    AudioSample sample = samples_[read_index_];
    read_index_ = (read_index_ + 1) % capacity_samples_;
    --count_;
    return sample;
}

void AudioBuffer::Clear() {
    read_index_ = 0;
    write_index_ = 0;
    count_ = 0;
    is_underrun_ = false;
}

double AudioBuffer::GetOccupancyPercentage() const {
    if (capacity_samples_ == 0)
        return 0.0;
    
    return (count_ / static_cast<double>(capacity_samples_)) * 100;
}

size_t AudioBuffer::GetCapacity() const {
    return capacity_samples_;
}

size_t AudioBuffer::GetAvailableSamplesCount() const {
    return count_;
}

bool AudioBuffer::IsUnderrun() const {
    return is_underrun_;
}