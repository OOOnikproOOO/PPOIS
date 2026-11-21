/**
 * @file Bookmark.cpp
 * @brief Implementation of Bookmark methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Bookmark.h"
#include <iomanip>
#include <sstream>
#include <cmath>

Bookmark::Bookmark(const std::string& track_title, double timestamp_sec, const std::string& note, const std::string& creation_date) :
    track_title_(track_title), timestamp_sec_(timestamp_sec >= 0.0 ? timestamp_sec : 0.0), note_(note), creation_date_(creation_date) {}

bool Bookmark::operator==(const Bookmark& other) const {
    const double kEpsilon = 1e-4;
    return track_title_ == other.track_title_ &&
           std::abs(timestamp_sec_ - other.timestamp_sec_) < kEpsilon &&
           note_ == other.note_ &&
           creation_date_ == other.creation_date_;
}

bool Bookmark::operator!=(const Bookmark& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Bookmark& bm) {
    os << bm.FormatBookmarkString();
    return os;
}

std::string Bookmark::FormatBookmarkString() const {
    int total_sec = static_cast<int>(timestamp_sec_);
    int minutes = total_sec / 60;
    int seconds = total_sec % 60;
    std::ostringstream oss;
    oss << track_title_ << " @ " << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds << " (" << note_ << ")";
    return oss.str();
}

void Bookmark::UpdateNote(const std::string& new_note) {
    note_ = new_note;
}

void Bookmark::AdjustTimestamp(double delta_sec) {
    timestamp_sec_ += delta_sec;
    if (timestamp_sec_ < 0.0)
        timestamp_sec_ = 0.0;
}

const std::string& Bookmark::GetTrackTitle() const {
    return track_title_;
}

double Bookmark::GetTimestampSec() const {
    return timestamp_sec_;
}

const std::string& Bookmark::GetNote() const {
    return note_;
}

const std::string& Bookmark::GetCreationDate() const {
    return creation_date_;
}