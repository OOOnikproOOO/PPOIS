/**
 * @file FLACDecoder.h
 * @brief Declaration of the FLACDecoder class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef FLACDECODER_H
#define FLACDECODER_H

#include <iostream>
#include <string>

/**
 * @brief Manages bit-exact lossless decompression and MD5 integrity verification for FLAC streams.
 */
class FLACDecoder {
public:
    /**
     * @brief Constructs a FLACDecoder.
     * @param compression_level Compression level (0 to 8).
     * @param block_size_samples Subframe block size in audio samples.
     */
    FLACDecoder(int compression_level = 5, int block_size_samples = 4096);

    bool operator==(const FLACDecoder& other) const;
    bool operator!=(const FLACDecoder& other) const;
    friend std::ostream& operator<<(std::ostream& os, const FLACDecoder& decoder);

    /**
     * @brief Decodes a FLAC audio block.
     * @param block_bytes Compressed block byte size.
     * @return Number of uncompressed samples recovered.
     */
    size_t DecodeBlock(size_t block_bytes);

    /**
     * @brief Validates stream integrity against stored MD5 signature.
     * @param calculated_md5 Calculated MD5 hash string.
     * @param expected_md5 Expected MD5 hash string from stream header.
     * @throws CorruptedAudioFileException if MD5 hashes do not match.
     */
    void VerifyChecksum(const std::string& calculated_md5, const std::string& expected_md5);

    /**
     * @brief Resets block counter and verification state.
     */
    void Reset();

    /**
     * @brief Calculates compression space savings ratio percentage.
     * @param raw_size Uncompressed PCM size.
     * @param compressed_size Compressed FLAC size.
     * @return Percentage size reduction (0.0 to 100.0%).
     */
    double CalculateCompressionRatio(size_t raw_size, size_t compressed_size) const;

    int GetCompressionLevel() const;
    int GetBlockSizeSamples() const;
    int GetDecodedBlocksCount() const;
    bool IsMd5Verified() const;

private:
    int compression_level_;
    int block_size_samples_;
    int decoded_blocks_count_;
    bool md5_verified_;
};

#endif