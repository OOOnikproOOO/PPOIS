/**
 * @file AudioCodec.h
 * @brief Declaration of the AudioCodec class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOCODEC_H
#define AUDIOCODEC_H

#include <iostream>
#include <string>

/**
 * @brief Represents encoding specifications, bitrates, and compression properties of an audio stream.
 */
class AudioCodec {
public:
    /**
     * @brief Constructs an AudioCodec.
     * @param codec_name Name of codec ("MP3", "FLAC", "WAV", "AAC").
     * @param bitrate_kbps Bitrate in kilobits per second.
     * @param sample_rate_hz Sample rate in Hertz (44100, 48000, 96000).
     * @param channels_count Channel count (1 for mono, 2 for stereo).
     * @param is_lossless Whether compression preserves original PCM bits.
     */
    AudioCodec(const std::string& codec_name = "MP3", int bitrate_kbps = 320, int sample_rate_hz = 44100, int channels_count = 2, bool is_lossless = false);

    /**
     * @brief Compares two AudioCodec instances for equality.
     * @param other Codec to compare with.
     * @return true if parameters match.
     */
    bool operator==(const AudioCodec& other) const;

    /**
     * @brief Compares two AudioCodec instances for inequality.
     * @param other Codec to compare with.
     * @return true if parameters differ.
     */
    bool operator!=(const AudioCodec& other) const;

    /**
     * @brief Stream output operator for formatting AudioCodec info.
     * @param os Output stream.
     * @param codec Codec instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioCodec& codec);

    /**
     * @brief Calculates stream throughput in bytes per second.
     * @return Data rate in bytes/sec.
     */
    size_t CalculateBytesPerSecond() const;

    /**
     * @brief Estimates audio file size in megabytes for a given track duration.
     * @param duration_sec Track duration in seconds.
     * @return Estimated megabytes.
     */
    double EstimateFileSizeMb(double duration_sec) const;

    /**
     * @brief Validates codec parameters.
     * @throws UnsupportedAudioFormatException if sample rate or channels are unsupported.
     */
    void ValidateParameters() const;

    /**
     * @brief Updates bitrate value with boundary checks.
     * @param bitrate New bitrate in kbps.
     */
    void SetBitrate(int bitrate);

    /**
     * @brief Gets codec algorithm name.
     * @return Reference to codec name string.
     */
    const std::string& GetCodecName() const;

    /**
     * @brief Gets transmission bitrate in kbps.
     * @return Bitrate in kbps.
     */
    int GetBitrateKbps() const;

    /**
     * @brief Gets audio sample rate in Hz.
     * @return Sample rate in Hertz.
     */
    int GetSampleRateHz() const;

    /**
     * @brief Gets channel count.
     * @return Number of channels (1 for mono, 2 for stereo).
     */
    int GetChannelsCount() const;

    /**
     * @brief Checks if codec compression is lossless.
     * @return true if lossless.
     */
    bool IsLossless() const;

private:
    std::string codec_name_;
    int bitrate_kbps_;
    int sample_rate_hz_;
    int channels_count_;
    bool is_lossless_;
};

#endif