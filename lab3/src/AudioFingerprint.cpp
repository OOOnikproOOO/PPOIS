/**
 * @file AudioFingerprint.cpp
 * @brief Implementation of AudioFingerprint methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioFingerprint.h"
#include <iomanip>
#include <sstream>
#include <cmath>

AudioFingerprint::AudioFingerprint(const std::string& fingerprint_hash, int algorithm_version, double confidence_score, double duration_analyzed_sec) :
    fingerprint_hash_(fingerprint_hash), algorithm_version_(algorithm_version < 1 ? 1 : algorithm_version), confidence_score_(confidence_score < 0.0 ? 0.0 : (confidence_score > 1.0 ? 1.0 : confidence_score)),
    duration_analyzed_sec_(duration_analyzed_sec < 0.0 ? 0.0 : duration_analyzed_sec) {}

bool AudioFingerprint::operator==(const AudioFingerprint& other) const {
    const double kEpsilon = 1e-4;
    return fingerprint_hash_ == other.fingerprint_hash_ &&
           algorithm_version_ == other.algorithm_version_ &&
           std::abs(confidence_score_ - other.confidence_score_) < kEpsilon;
}

bool AudioFingerprint::operator!=(const AudioFingerprint& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioFingerprint& fp) {
    os << "AcousticFP[" << (fp.fingerprint_hash_.empty() ? "None" : fp.fingerprint_hash_.substr(0, 8) + "...") << ", Confidence: " << (fp.confidence_score_ * 100) << "%]";
    return os;
}

void AudioFingerprint::GenerateFromBuffer(const AudioBuffer& buffer) {
    size_t count = buffer.GetAvailableSamplesCount();
    if (count == 0) {
        fingerprint_hash_ = "0000000000000000";
        confidence_score_ = 0.0;
        return;
    }

    size_t capacity = buffer.GetCapacity();
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << (count * 2654435761u) << std::setw(8) << (capacity * 2246822519u);

    fingerprint_hash_ = oss.str();
    confidence_score_ = 0.95;
}

double AudioFingerprint::MatchConfidence(const AudioFingerprint& other) const {
    if (!IsValid() || !other.IsValid())
        return 0.0;

    if (fingerprint_hash_ == other.fingerprint_hash_)
        return confidence_score_ * other.confidence_score_;

    size_t matches = 0;
    size_t min_len = std::min(fingerprint_hash_.length(), other.fingerprint_hash_.length());
    if (min_len == 0)
        return 0.0;

    for (size_t i = 0; i < min_len; i++) {
        if (fingerprint_hash_[i] == other.fingerprint_hash_[i])
            matches++;
    }

    return (static_cast<double>(matches) / min_len) * confidence_score_ * other.confidence_score_;
}

bool AudioFingerprint::IsValid() const {
    return !fingerprint_hash_.empty() && confidence_score_ > 0.0;
}

void AudioFingerprint::Clear() {
    fingerprint_hash_.clear();
    confidence_score_ = 0.0;
}

const std::string& AudioFingerprint::GetFingerprintHash() const {
    return fingerprint_hash_;
}

int AudioFingerprint::GetAlgorithmVersion() const {
    return algorithm_version_;
}

double AudioFingerprint::GetConfidenceScore() const {
    return confidence_score_;
}

double AudioFingerprint::GetDurationAnalyzedSec() const {
    return duration_analyzed_sec_;
}