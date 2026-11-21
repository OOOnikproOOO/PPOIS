/**
 * @file MP3Decoder.cpp
 * @brief Implementation of MP3Decoder methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "MP3Decoder.h"

MP3Decoder::MP3Decoder(bool is_vbr, int id3_version, int frame_size_bytes) : is_vbr_(is_vbr), id3_version_(id3_version), frame_size_bytes_(frame_size_bytes), decoded_frames_count_(0) {}

bool MP3Decoder::operator==(const MP3Decoder& other) const {
    return is_vbr_ == other.is_vbr_ &&
           id3_version_ == other.id3_version_ &&
           frame_size_bytes_ == other.frame_size_bytes_ &&
           decoded_frames_count_ == other.decoded_frames_count_;
}

bool MP3Decoder::operator!=(const MP3Decoder& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const MP3Decoder& decoder) {
    os << "MP3Decoder[Frames:" << decoder.decoded_frames_count_ << ", ID3v" << decoder.id3_version_ << ", " << (decoder.is_vbr_ ? "VBR" : "CBR") << "]";
    return os;
}

size_t MP3Decoder::DecodeFrame(size_t raw_bytes) {
    const size_t kSamplesPerMp3Frame = 1152;
    if (raw_bytes >= static_cast<size_t>(frame_size_bytes_)) {
        decoded_frames_count_++;
        return kSamplesPerMp3Frame;
    }
    return 0;
}

bool MP3Decoder::ParseHeader(size_t header_bytes) {
    const size_t kMinId3HeaderBytes = 10;
    return header_bytes >= kMinId3HeaderBytes;
}

void MP3Decoder::ResetDecoder() {
    decoded_frames_count_ = 0;
}

double MP3Decoder::CalculateDecodedDurationSec(size_t total_bytes, int bitrate_kbps) const {
    if (bitrate_kbps <= 0)
        return 0.0;
    
    const double kBitsPerByte = 8.0;
    double total_bits = static_cast<double>(total_bytes) * kBitsPerByte;
    return total_bits / (static_cast<double>(bitrate_kbps) * 1000);
}

bool MP3Decoder::IsVbr() const {
    return is_vbr_;
}

int MP3Decoder::GetId3Version() const {
    return id3_version_;
}

int MP3Decoder::GetFrameSizeBytes() const {
    return frame_size_bytes_;
}

int MP3Decoder::GetDecodedFramesCount() const {
    return decoded_frames_count_;
}