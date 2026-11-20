/**
 * @file StreamDownloader.h
 * @brief Declaration of the StreamDownloader class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef STREAMDOWNLOADER_H
#define STREAMDOWNLOADER_H

#include <iostream>
#include <string>

/**
 * @brief Manages streaming track pre-buffering and offline local file downloading with progress tracking.
 */
class StreamDownloader {
public:
    /**
     * @brief Constructs a StreamDownloader.
     * @param download_url Remote resource URL to fetch.
     * @param total_bytes Total payload size in bytes.
     * @param is_completed Download completion flag.
     */
    StreamDownloader(const std::string& download_url = "http://cdn.music.com/audio.mp3", size_t total_bytes = 10485760, bool is_completed = false);

    /**
     * @brief Compares two StreamDownloader instances for equality.
     * @param other Downloader to compare with.
     * @return true if properties match.
     */
    bool operator==(const StreamDownloader& other) const;

    /**
     * @brief Compares two StreamDownloader instances for inequality.
     * @param other Downloader to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const StreamDownloader& other) const;

    /**
     * @brief Stream output operator for formatting StreamDownloader info.
     * @param os Output stream.
     * @param dl Downloader instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const StreamDownloader& dl);

    /**
     * @brief Ingests an incoming downloaded chunk and updates speed estimate.
     * @param chunk_bytes Newly downloaded byte chunk.
     * @param elapsed_sec Time delta in seconds spent downloading chunk.
     */
    void ProcessChunk(size_t chunk_bytes, double elapsed_sec);

    /**
     * @brief Computes download progress percentage (0.0 to 100.0%).
     * @return Completion percentage.
     */
    double CalculateProgressPercentage() const;

    /**
     * @brief Aborts and resets downloading process.
     */
    void Cancel();

    /**
     * @brief Sets remote download URL.
     * @param url Download source URL.
     */
    void SetUrl(const std::string& url);

    /**
     * @brief Gets remote source URL.
     * @return Reference to URL string.
     */
    const std::string& GetDownloadUrl() const;

    /**
     * @brief Gets number of bytes received so far.
     * @return Downloaded bytes.
     */
    size_t GetBytesDownloaded() const;

    /**
     * @brief Gets total target file size in bytes.
     * @return Total bytes.
     */
    size_t GetTotalBytes() const;

    /**
     * @brief Gets instantaneous download speed in KB/s.
     * @return Speed in KB/s.
     */
    double GetDownloadSpeedKbps() const;

    /**
     * @brief Checks if download has finished completely.
     * @return true if completed.
     */
    bool IsCompleted() const;

private:
    std::string download_url_;
    size_t bytes_downloaded_;
    size_t total_bytes_;
    double download_speed_kbps_;
    bool is_completed_;
};

#endif