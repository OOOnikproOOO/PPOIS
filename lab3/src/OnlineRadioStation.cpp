/**
 * @file OnlineRadioStation.cpp
 * @brief Implementation of OnlineRadioStation methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "OnlineRadioStation.h"
#include "StreamingNetworkException.h"
#include <sstream>

OnlineRadioStation::OnlineRadioStation(const std::string& station_name, const std::string& stream_url, const std::string& genre, int bitrate_kbps, bool is_online) :
    station_name_(station_name), stream_url_(stream_url), genre_(genre), bitrate_kbps_(bitrate_kbps < 32 ? 32 : (bitrate_kbps > 512 ? 512 : bitrate_kbps)), is_online_(is_online) {}

bool OnlineRadioStation::operator==(const OnlineRadioStation& other) const {
    return station_name_ == other.station_name_ &&
           stream_url_ == other.stream_url_ &&
           genre_ == other.genre_ &&
           bitrate_kbps_ == other.bitrate_kbps_ &&
           is_online_ == other.is_online_;
}

bool OnlineRadioStation::operator!=(const OnlineRadioStation& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const OnlineRadioStation& station) {
    os << station.FormatStationInfo();
    return os;
}

void OnlineRadioStation::Connect() {
    if (stream_url_.empty() || stream_url_.rfind("http", 0) != 0)
        throw StreamingNetworkException("Failed to connect to radio stream: invalid URL '" + stream_url_ + "'");

    is_online_ = true;
}

void OnlineRadioStation::Disconnect() {
    is_online_ = false;
}

std::string OnlineRadioStation::FormatStationInfo() const {
    std::ostringstream oss;
    oss << station_name_ << " [" << genre_ << ", " << bitrate_kbps_ << " kbps] (" << (is_online_ ? "ONLINE" : "OFFLINE") << ")";
    return oss.str();
}

void OnlineRadioStation::SetStreamUrl(const std::string& url) {
    stream_url_ = url;
}

const std::string& OnlineRadioStation::GetStationName() const {
    return station_name_;
}

const std::string& OnlineRadioStation::GetStreamUrl() const {
    return stream_url_;
}

const std::string& OnlineRadioStation::GetGenre() const {
    return genre_;
}

int OnlineRadioStation::GetBitrateKbps() const {
    return bitrate_kbps_;
}

bool OnlineRadioStation::IsOnline() const {
    return is_online_;
}