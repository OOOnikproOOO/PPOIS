/**
 * @file WAVDecoder.cpp
 * @brief Implementation of WAVDecoder methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "WAVDecoder.h"
#include "CorruptedAudioFileException.h"

WAVDecoder::WAVDecoder(int audio_format_code, int data_chunk_size_bytes) :
    is_riff_valid_(false), audio_format_code_(audio_format_code), data_chunk_size_bytes_(data_chunk_size_bytes), bytes_read_(0) {}

bool WAVDecoder::operator==(const WAVDecoder& other) const {
    return is_riff_valid_ == other.is_riff_valid_ &&
           audio_format_code_ == other.audio_format_code_ &&
           data_chunk_size_bytes_ == other.data_chunk_size_bytes_ &&
           bytes_read_ == other.bytes_read_;
}

bool WAVDecoder::operator!=(const WAVDecoder& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const WAVDecoder& decoder) {
    os << "WAVDecoder[Format:" << decoder.audio_format_code_ << ", DataChunk:" << decoder.data_chunk_size_bytes_ << " bytes, Read:" << decoder.bytes_read_ << "]";
    return os;
}

void WAVDecoder::ParseRiffHeader(size_t header_size) {
    const size_t kStandardWavHeaderBytes = 44;
    if (header_size < kStandardWavHeaderBytes) {
        is_riff_valid_ = false;
        throw CorruptedAudioFileException("Truncated WAV header: file is smaller than 44-byte RIFF header.");
    }
    is_riff_valid_ = true;
}

size_t WAVDecoder::ReadPcmData(size_t chunk_bytes) {
    bytes_read_ += static_cast<int>(chunk_bytes);
    return chunk_bytes;
}

size_t WAVDecoder::CalculateTotalSamples(int bytes_per_sample) const {
    if (bytes_per_sample <= 0 || data_chunk_size_bytes_ <= 0)
        return 0;
    
    return static_cast<size_t>(data_chunk_size_bytes_ / bytes_per_sample);
}

void WAVDecoder::Reset() {
    is_riff_valid_ = false;
    bytes_read_ = 0;
}

bool WAVDecoder::IsRiffValid() const {
    return is_riff_valid_;
}

int WAVDecoder::GetAudioFormatCode() const {
    return audio_format_code_;
}

int WAVDecoder::GetDataChunkSizeBytes() const {
    return data_chunk_size_bytes_;
}

int WAVDecoder::GetBytesRead() const {
    return bytes_read_;
}