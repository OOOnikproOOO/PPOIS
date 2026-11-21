/**
 * @file PlaybackStatistics.cpp
 * @brief Implementation of PlaybackStatistics methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PlaybackStatistics.h"
#include <iomanip>
#include <sstream>
#include <cmath>

PlaybackStatistics::PlaybackStatistics(double total_listen_time_sec, int sessions_count, int skips_count, const std::string& favorite_genre) :
    total_listen_time_sec_(total_listen_time_sec < 0.0 ? 0.0 : total_listen_time_sec), sessions_count_(sessions_count < 0 ? 0 : sessions_count), skips_count_(skips_count < 0 ? 0 : skips_count), favorite_genre_(favorite_genre) {}

bool PlaybackStatistics::operator==(const PlaybackStatistics& other) const {
    const double kEpsilon = 1e-4;
    return std::abs(total_listen_time_sec_ - other.total_listen_time_sec_) < kEpsilon &&
           sessions_count_ == other.sessions_count_ &&
           skips_count_ == other.skips_count_ &&
           favorite_genre_ == other.favorite_genre_;
}

bool PlaybackStatistics::operator!=(const PlaybackStatistics& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PlaybackStatistics& stats) {
    os << "PlaybackStats[" << std::fixed << std::setprecision(1) << (stats.total_listen_time_sec_ / 60.0) << " mins, " << stats.sessions_count_ << " plays, Fav: " << stats.favorite_genre_ << "]";
    return os;
}

void PlaybackStatistics::RecordSession(double listen_duration_sec, const std::string& genre, bool skipped) {
    if (listen_duration_sec > 0.0)
        total_listen_time_sec_ += listen_duration_sec;

    sessions_count_++;
    if (skipped)
        skips_count_++;

    if (!genre.empty())
        favorite_genre_ = genre;
}

double PlaybackStatistics::GetAverageSessionMinutes() const {
    if (sessions_count_ <= 0)
        return 0.0;

    return (total_listen_time_sec_ / sessions_count_) / 60.0;
}

double PlaybackStatistics::CalculateSkipRatePercentage() const {
    if (sessions_count_ <= 0)
        return 0.0;

    return (static_cast<double>(skips_count_) / sessions_count_) * 100.0;
}

void PlaybackStatistics::Reset() {
    total_listen_time_sec_ = 0.0;
    sessions_count_ = 0;
    skips_count_ = 0;
    favorite_genre_ = "Unknown";
}

double PlaybackStatistics::GetTotalListenTimeSec() const {
    return total_listen_time_sec_;
}

int PlaybackStatistics::GetSessionsCount() const {
    return sessions_count_;
}

int PlaybackStatistics::GetSkipsCount() const {
    return skips_count_;
}

const std::string& PlaybackStatistics::GetFavoriteGenre() const {
    return favorite_genre_;
}