/**
 * @file StreamDownloader.cpp
 * @brief Implementation of StreamDownloader methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "StreamDownloader.h"
#include <iomanip>
#include <sstream>
#include <cmath>

StreamDownloader::StreamDownloader(const std::string& download_url, size_t total_bytes, bool is_completed) :
    download_url_(download_url), bytes_downloaded_(is_completed ? total_bytes : 0), total_bytes_(total_bytes), download_speed_kbps_(0.0), is_completed_(is_completed) {}

bool StreamDownloader::operator==(const StreamDownloader& other) const {
    const double kEpsilon = 1e-4;
    return download_url_ == other.download_url_ &&
           bytes_downloaded_ == other.bytes_downloaded_ &&
           total_bytes_ == other.total_bytes_ &&
           std::abs(download_speed_kbps_ - other.download_speed_kbps_) < kEpsilon &&
           is_completed_ == other.is_completed_;
}

bool StreamDownloader::operator!=(const StreamDownloader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const StreamDownloader& dl) {
    os << "Downloader[" << std::fixed << std::setprecision(1) << dl.CalculateProgressPercentage() << "%, Speed: " << dl.download_speed_kbps_ << " KB/s (" << (dl.is_completed_ ? "DONE" : "IN PROGRESS") << ")]";
    return os;
}

void StreamDownloader::ProcessChunk(size_t chunk_bytes, double elapsed_sec) {
    bytes_downloaded_ += chunk_bytes;
    if (bytes_downloaded_ >= total_bytes_) {
        bytes_downloaded_ = total_bytes_;
        is_completed_ = true;
    }

    if (elapsed_sec > 0.0)
        download_speed_kbps_ = (static_cast<double>(chunk_bytes) / 1024.0) / elapsed_sec;
}

double StreamDownloader::CalculateProgressPercentage() const {
    if (total_bytes_ == 0)
        return 0.0;

    double pct = (static_cast<double>(bytes_downloaded_) / total_bytes_) * 100;
    if (pct > 100.0)
        return 100.0;

    return pct;
}

void StreamDownloader::Cancel() {
    bytes_downloaded_ = 0;
    download_speed_kbps_ = 0.0;
    is_completed_ = false;
}

void StreamDownloader::SetUrl(const std::string& url) {
    download_url_ = url;
}

const std::string& StreamDownloader::GetDownloadUrl() const {
    return download_url_;
}

size_t StreamDownloader::GetBytesDownloaded() const {
    return bytes_downloaded_;
}

size_t StreamDownloader::GetTotalBytes() const {
    return total_bytes_;
}

double StreamDownloader::GetDownloadSpeedKbps() const {
    return download_speed_kbps_;
}

bool StreamDownloader::IsCompleted() const {
    return is_completed_;
}