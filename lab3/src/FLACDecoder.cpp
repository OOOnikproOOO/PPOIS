/**
 * @file FLACDecoder.cpp
 * @brief Implementation of FLACDecoder methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "FLACDecoder.h"
#include "CorruptedAudioFileException.h"

FLACDecoder::FLACDecoder(int compression_level, int block_size_samples) : compression_level_(compression_level), block_size_samples_(block_size_samples), decoded_blocks_count_(0), md5_verified_(false) {}

bool FLACDecoder::operator==(const FLACDecoder& other) const {
    return compression_level_ == other.compression_level_ &&
           block_size_samples_ == other.block_size_samples_ &&
           decoded_blocks_count_ == other.decoded_blocks_count_ &&
           md5_verified_ == other.md5_verified_;
}

bool FLACDecoder::operator!=(const FLACDecoder& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const FLACDecoder& decoder) {
    os << "FLACDecoder[Level:" << decoder.compression_level_ << ", Block:" << decoder.block_size_samples_ << ", MD5:" << (decoder.md5_verified_ ? "Verified" : "Pending") << "]";
    return os;
}

size_t FLACDecoder::DecodeBlock(size_t block_bytes) {
    if (block_bytes > 0) {
        decoded_blocks_count_++;
        return static_cast<size_t>(block_size_samples_);
    }
    return 0;
}

void FLACDecoder::VerifyChecksum(const std::string& calculated_md5, const std::string& expected_md5) {
    if (calculated_md5 != expected_md5) {
        md5_verified_ = false;
        throw CorruptedAudioFileException("FLAC MD5 checksum verification failed: audio stream is corrupted.");
    }
    md5_verified_ = true;
}

void FLACDecoder::Reset() {
    decoded_blocks_count_ = 0;
    md5_verified_ = false;
}

double FLACDecoder::CalculateCompressionRatio(size_t raw_size, size_t compressed_size) const {
    if (raw_size == 0)
        return 0.0;
    
    double ratio = (1 - (compressed_size/ static_cast<double>(raw_size))) * 100;
    return ratio > 0.0 ? ratio : 0.0;
}

int FLACDecoder::GetCompressionLevel() const {
    return compression_level_;
}

int FLACDecoder::GetBlockSizeSamples() const {
    return block_size_samples_;
}

int FLACDecoder::GetDecodedBlocksCount() const {
    return decoded_blocks_count_;
}

bool FLACDecoder::IsMd5Verified() const {
    return md5_verified_;
}