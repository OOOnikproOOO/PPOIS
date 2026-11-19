/**
 * @file WAVDecoder.h
 * @brief Declaration of the WAVDecoder class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef WAVDECODER_H
#define WAVDECODER_H

#include <iostream>

/**
 * @brief Parses RIFF chunk headers and decodes linear uncompressed PCM audio blocks.
 */
class WAVDecoder {
public:
    /**
     * @brief Constructs a WAVDecoder.
     * @param audio_format_code Format tag (1 for uncompressed linear PCM).
     * @param data_chunk_size_bytes Declared byte size of 'data' chunk.
     */
    WAVDecoder(int audio_format_code = 1, int data_chunk_size_bytes = 0);

    /**
     * @brief Compares two WAVDecoder instances for equality.
     * @param other Decoder to compare with.
     * @return true if properties match.
     */
    bool operator==(const WAVDecoder& other) const;

    /**
     * @brief Compares two WAVDecoder instances for inequality.
     * @param other Decoder to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const WAVDecoder& other) const;

    /**
     * @brief Stream output operator for formatting WAVDecoder info.
     * @param os Output stream.
     * @param decoder Decoder instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const WAVDecoder& decoder);

    /**
     * @brief Validates standard 44-byte RIFF WAVE header signature.
     * @param header_size Number of header bytes available.
     * @throws CorruptedAudioFileException if header size is shorter than standard 44 bytes.
     */
    void ParseRiffHeader(size_t header_size);

    /**
     * @brief Reads a chunk of raw linear PCM bytes.
     * @param chunk_bytes Bytes to consume.
     * @return Number of bytes actually read.
     */
    size_t ReadPcmData(size_t chunk_bytes);

    /**
     * @brief Computes total samples in the WAV audio data chunk.
     * @param bytes_per_sample Byte width per multi-channel sample (e.g. 4 for 16-bit stereo).
     * @return Total sample count.
     */
    size_t CalculateTotalSamples(int bytes_per_sample) const;

    /**
     * @brief Resets read position and validation flags.
     */
    void Reset();

    /**
     * @brief Checks if RIFF header format is valid.
     * @return true if valid.
     */
    bool IsRiffValid() const;

    /**
     * @brief Gets audio format code (1 = PCM).
     * @return Format code integer.
     */
    int GetAudioFormatCode() const;

    /**
     * @brief Gets data chunk size in bytes.
     * @return Size in bytes.
     */
    int GetDataChunkSizeBytes() const;

    /**
     * @brief Gets total number of PCM bytes read so far.
     * @return Read bytes count.
     */
    int GetBytesRead() const;

private:
    bool is_riff_valid_;
    int audio_format_code_;
    int data_chunk_size_bytes_;
    int bytes_read_;
};

#endif