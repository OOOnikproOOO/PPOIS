/**
 * @file PodcastShow.cpp
 * @brief Implementation of PodcastShow methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PodcastShow.h"
#include "TrackNotFoundException.h"
#include <sstream>

PodcastShow::PodcastShow(const std::string& show_title, const std::string& host_name, const std::string& category) : show_title_(show_title), host_name_(host_name), category_(category) {}

bool PodcastShow::operator==(const PodcastShow& other) const {
    return show_title_ == other.show_title_ &&
           host_name_ == other.host_name_ &&
           category_ == other.category_ &&
           episodes_ == other.episodes_;
}

bool PodcastShow::operator!=(const PodcastShow& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PodcastShow& show) {
    os << "PodcastShow['" << show.show_title_ << "' by " << show.host_name_ << " (" << show.category_ << "), " << show.episodes_.size() << " eps]";
    return os;
}

void PodcastShow::AddEpisode(const PodcastEpisode& episode) {
    episodes_.push_back(episode);
}

const PodcastEpisode& PodcastShow::FindEpisode(int episode_number) const {
    for (const auto& ep : episodes_) {
        if (ep.GetEpisodeNumber() == episode_number)
            return ep;
    }

    throw TrackNotFoundException("Podcast episode #" + std::to_string(episode_number) + " not found in show '" + show_title_ + "'.");
}

size_t PodcastShow::GetUnlistenedCount() const {
    size_t count = 0;
    for (const auto& ep : episodes_) {
        if (!ep.IsListened())
            count++;
    }

    return count;
}

double PodcastShow::CalculateTotalDurationSec() const {
    double total = 0.0;
    for (const auto& ep : episodes_)
        total += ep.GetDurationSec();

    return total;
}

const std::string& PodcastShow::GetShowTitle() const {
    return show_title_;
}

const std::string& PodcastShow::GetHostName() const {
    return host_name_;
}

const std::string& PodcastShow::GetCategory() const {
    return category_;
}

const std::vector<PodcastEpisode>& PodcastShow::GetEpisodes() const {
    return episodes_;
}