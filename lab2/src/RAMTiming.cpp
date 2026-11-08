/**
 * @file RAMTiming.cpp
 * @brief Implementation of RAMTiming methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "RAMTiming.h"

RAMTiming::RAMTiming(int cas_latency, int trcd, int trp, int tras, int command_rate) : 
    cas_latency_(cas_latency), trcd_(trcd), trp_(trp), tras_(tras), command_rate_(command_rate) {}

bool RAMTiming::operator==(const RAMTiming& other) const {
    return (cas_latency_ == other.cas_latency_ &&
            trcd_ == other.trcd_ &&
            trp_ == other.trp_ &&
            tras_ == other.tras_ &&
            command_rate_ == other.command_rate_);
}

bool RAMTiming::operator!=(const RAMTiming& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const RAMTiming& timing) {
    os << timing.cas_latency_ << "-" << timing.trcd_ << "-" << timing.trp_ << "-" << timing.tras_ << " (" << timing.command_rate_ << "T)";
    return os;
}

double RAMTiming::CalculateTrueLatencyNs(int frequency_mhz) const {
    if (frequency_mhz <= 0)
        return 0.0;
 
    return (2000.0 * static_cast<double>(cas_latency_)) / frequency_mhz;
}

bool RAMTiming::ValidateTimings() const {
    if (cas_latency_ <= 0 || trcd_ <= 0 || trp_ <= 0 || tras_ <= 0)
        return false;
 
    return (tras_ >= cas_latency_ + trcd_);
}

void RAMTiming::OptimizeForFrequency(int target_freq_mhz) {
    if (target_freq_mhz >= 4800) {
        cas_latency_ = 36;
        trcd_ = 36;
        trp_ = 36;
        tras_ = 76;
    } else 
        if (target_freq_mhz >= 3200) {
            cas_latency_ = 16;
            trcd_ = 18;
            trp_ = 18;
            tras_ = 36;
        } else {
                cas_latency_ = 14;
                trcd_ = 14;
                trp_ = 14;
                tras_ = 32;
          }
}

bool RAMTiming::IsFasterThan(const RAMTiming& other, int freq_this, int freq_other) const {
    return CalculateTrueLatencyNs(freq_this) < other.CalculateTrueLatencyNs(freq_other);
}

int RAMTiming::GetCasLatency() const {
    return cas_latency_;
}

int RAMTiming::GetTrcd() const {
    return trcd_;
}

int RAMTiming::GetTrp() const {
    return trp_;
}

int RAMTiming::GetTras() const {
    return tras_;
}

int RAMTiming::GetCommandRate() const {
    return command_rate_;
}