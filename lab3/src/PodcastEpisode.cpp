/**
 * @file PodcastEpisode.cpp
 * @brief Implementation of PodcastEpisode methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PodcastEpisode.h"
#include <sstream>
#include <cmath>

PodcastEpisode::PodcastEpisode(const std::string& title, int episode_number, double duration_sec, const std::string& release_date, bool is_listened) :
    title_(title), episode_number_(episode_number < 1 ? 1 : episode_number), duration_sec_(duration_sec < 0.0 ? 0.0 : duration_sec), release_date_(release_date), is_listened_(is_listened) {}

bool PodcastEpisode::operator==(const PodcastEpisode& other) const {
    const double kEpsilon = 1e-4;
    return title_ == other.title_ &&
           episode_number_ == other.episode_number_ &&
           std::abs(duration_sec_ - other.duration_sec_) < kEpsilon &&
           release_date_ == other.release_date_;
}

bool PodcastEpisode::operator!=(const PodcastEpisode& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PodcastEpisode& ep) {
    os << ep.FormatEpisodeSummary();
    return os;
}

void PodcastEpisode::MarkAsListened(bool listened) {
    is_listened_ = listened;
}

std::string PodcastEpisode::FormatEpisodeSummary() const {
    int minutes = static_cast<int>(duration_sec_ / 60.0);
    std::ostringstream oss;
    oss << "#" << episode_number_ << ": " << title_ << " (" << minutes << " min, " << release_date_ << ") " << (is_listened_ ? "[Listened]" : "[New]");
    return oss.str();
}

void PodcastEpisode::UpdateDuration(double sec) {
    if (sec >= 0.0)
        duration_sec_ = sec;
}

const std::string& PodcastEpisode::GetTitle() const {
    return title_;
}

int PodcastEpisode::GetEpisodeNumber() const {
    return episode_number_;
}

double PodcastEpisode::GetDurationSec() const {
    return duration_sec_;
}

const std::string& PodcastEpisode::GetReleaseDate() const {
    return release_date_;
}

bool PodcastEpisode::IsListened() const {
    return is_listened_;
}