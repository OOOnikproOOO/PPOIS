/**
 * @file MP3Decoder.h
 * @brief Declaration of the MP3Decoder class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MP3DECODER_H
#define MP3DECODER_H

#include <iostream>
#include <vector>

/**
 * @brief Handles MPEG Layer-3 bitstream frame decompression and ID3 metadata header parsing.
 */
class MP3Decoder {
public:
    /**
     * @brief Constructs an MP3Decoder instance.
     * @param is_vbr Whether stream uses Variable Bit Rate.
     * @param id3_version Major ID3 tag version (e.g. 2 for ID3v2.4).
     * @param frame_size_bytes Average frame size in bytes.
     */
    MP3Decoder(bool is_vbr = false, int id3_version = 2, int frame_size_bytes = 417);

    bool operator==(const MP3Decoder& other) const;
    bool operator!=(const MP3Decoder& other) const;
    friend std::ostream& operator<<(std::ostream& os, const MP3Decoder& decoder);

    /**
     * @brief Decodes an MPEG frame from raw bytes.
     * @param raw_bytes Size of raw compressed chunk in bytes.
     * @return Number of PCM samples produced.
     */
    size_t DecodeFrame(size_t raw_bytes);

    /**
     * @brief Parses ID3 tag header chunk.
     * @param header_bytes Size of header bytes.
     * @return true if valid ID3 header was recognized.
     */
    bool ParseHeader(size_t header_bytes);

    /**
     * @brief Resets frame counter and decoder state.
     */
    void ResetDecoder();

    /**
     * @brief Computes playback duration in seconds for decoded stream bytes.
     * @param total_bytes Total MP3 file bytes.
     * @param bitrate_kbps Stream bitrate.
     * @return Duration in seconds.
     */
    double CalculateDecodedDurationSec(size_t total_bytes, int bitrate_kbps) const;

    bool IsVbr() const;
    int GetId3Version() const;
    int GetFrameSizeBytes() const;
    int GetDecodedFramesCount() const;

private:
    bool is_vbr_;
    int id3_version_;
    int frame_size_bytes_;
    int decoded_frames_count_;
};

#endif