/**
 * @file AudioFingerprint.h
 * @brief Declaration of the AudioFingerprint class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOFINGERPRINT_H
#define AUDIOFINGERPRINT_H

#include <iostream>
#include <string>
#include "AudioBuffer.h"

/**
 * @brief Generates acoustic hashing signatures from audio streams for song identification and deduplication.
 */
class AudioFingerprint {
public:
    /**
     * @brief Constructs an AudioFingerprint.
     * @param fingerprint_hash Hexadecimal acoustic hash string.
     * @param algorithm_version Fingerprinting algorithm version.
     * @param confidence_score Match probability confidence (0.0 to 1.0).
     * @param duration_analyzed_sec Duration of audio analyzed in seconds.
     */
    AudioFingerprint(const std::string& fingerprint_hash = "", int algorithm_version = 1, double confidence_score = 1.0, double duration_analyzed_sec = 10.0);

    /**
     * @brief Compares two AudioFingerprint instances for equality.
     * @param other Fingerprint to compare with.
     * @return true if hash and algorithm match.
     */
    bool operator==(const AudioFingerprint& other) const;

    /**
     * @brief Compares two AudioFingerprint instances for inequality.
     * @param other Fingerprint to compare with.
     * @return true if hash or algorithm differ.
     */
    bool operator!=(const AudioFingerprint& other) const;

    /**
     * @brief Stream output operator for formatting AudioFingerprint info.
     * @param os Output stream.
     * @param fp Fingerprint instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioFingerprint& fp);

    /**
     * @brief Computes fingerprint hash from samples stored in an AudioBuffer.
     * @param buffer Input AudioBuffer.
     */
    void GenerateFromBuffer(const AudioBuffer& buffer);

    /**
     * @brief Compares this fingerprint with another and computes similarity match score (0.0 to 1.0).
     * @param other Fingerprint to compare against.
     * @return Match similarity coefficient.
     */
    double MatchConfidence(const AudioFingerprint& other) const;

    /**
     * @brief Checks if fingerprint hash is valid and non-empty.
     * @return true if valid.
     */
    bool IsValid() const;

    /**
     * @brief Clears fingerprint hash and resets confidence.
     */
    void Clear();

    /**
     * @brief Gets acoustic hash string.
     * @return Reference to hash string.
     */
    const std::string& GetFingerprintHash() const;

    /**
     * @brief Gets algorithm version number.
     * @return Version integer.
     */
    int GetAlgorithmVersion() const;

    /**
     * @brief Gets recognition confidence score (0.0 to 1.0).
     * @return Confidence score.
     */
    double GetConfidenceScore() const;

    /**
     * @brief Gets analyzed duration in seconds.
     * @return Duration in seconds.
     */
    double GetDurationAnalyzedSec() const;

private:
    std::string fingerprint_hash_;
    int algorithm_version_;
    double confidence_score_;
    double duration_analyzed_sec_;
};

#endif