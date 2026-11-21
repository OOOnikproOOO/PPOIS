/**
 * @file OnlineRadioStation.h
 * @brief Declaration of the OnlineRadioStation class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef ONLINERADIOSTATION_H
#define ONLINERADIOSTATION_H

#include <iostream>
#include <string>

/**
 * @brief Represents an internet radio stream with streaming endpoint URLs and connectivity status.
 */
class OnlineRadioStation {
public:
    /**
     * @brief Constructs an OnlineRadioStation.
     * @param station_name Radio broadcaster name.
     * @param stream_url Live HTTP/ICY streaming URL.
     * @param genre Music/content genre.
     * @param bitrate_kbps Broadcast bitrate in kbps.
     * @param is_online Online connectivity status.
     */
    OnlineRadioStation(const std::string& station_name = "Cosmic Chillout Radio", const std::string& stream_url = "http://radio.stream.fm:8000/live", const std::string& genre = "Ambient", int bitrate_kbps = 320, bool is_online = true);

    /**
     * @brief Compares two OnlineRadioStation instances for equality.
     * @param other Station to compare with.
     * @return true if URL and properties match.
     */
    bool operator==(const OnlineRadioStation& other) const;

    /**
     * @brief Compares two OnlineRadioStation instances for inequality.
     * @param other Station to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const OnlineRadioStation& other) const;

    /**
     * @brief Stream output operator for formatting OnlineRadioStation info.
     * @param os Output stream.
     * @param station Station instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const OnlineRadioStation& station);

    /**
     * @brief Connects to remote radio stream server.
     * @throws StreamingNetworkException if stream URL is invalid or empty.
     */
    void Connect();

    /**
     * @brief Disconnects from radio stream and resets connectivity status.
     */
    void Disconnect();

    /**
     * @brief Formats station summary as 'Name [Genre, Bitrate kbps]'.
     * @return Formatted string.
     */
    std::string FormatStationInfo() const;

    /**
     * @brief Updates stream URL endpoint.
     * @param url New stream URL.
     */
    void SetStreamUrl(const std::string& url);

    /**
     * @brief Gets station broadcaster name.
     * @return Reference to station name string.
     */
    const std::string& GetStationName() const;

    /**
     * @brief Gets HTTP/ICY streaming URL.
     * @return Reference to stream URL string.
     */
    const std::string& GetStreamUrl() const;

    /**
     * @brief Gets station music genre.
     * @return Reference to genre string.
     */
    const std::string& GetGenre() const;

    /**
     * @brief Gets broadcast transmission bitrate in kbps.
     * @return Bitrate in kbps.
     */
    int GetBitrateKbps() const;

    /**
     * @brief Checks if station is currently streaming online.
     * @return true if connected online.
     */
    bool IsOnline() const;

private:
    std::string station_name_;
    std::string stream_url_;
    std::string genre_;
    int bitrate_kbps_;
    bool is_online_;
};

#endif