/**
 * @file AlbumArt.h
 * @brief Declaration of the AlbumArt class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef ALBUMART_H
#define ALBUMART_H

#include <iostream>
#include <string>

/**
 * @brief Represents embedded album artwork image data, mime types and pixel dimensions.
 */
class AlbumArt {
public:
    /**
     * @brief Constructs an AlbumArt.
     * @param mime_type Media format type (".jpeg", ".png").
     * @param width Width in pixels.
     * @param height Height in pixels.
     * @param data_size_bytes Byte size of embedded picture data.
     */
    AlbumArt(const std::string& mime_type = ".jpeg", int width = 500, int height = 500, size_t data_size_bytes = 102400);

    /**
     * @brief Compares two AlbumArt instances for equality.
     * @param other Artwork to compare with.
     * @return true if properties match.
     */
    bool operator==(const AlbumArt& other) const;

    /**
     * @brief Compares two AlbumArt instances for inequality.
     * @param other Artwork to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const AlbumArt& other) const;

    /**
     * @brief Stream output operator for formatting AlbumArt info.
     * @param os Output stream.
     * @param art Artwork instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AlbumArt& art);

    /**
     * @brief Checks if image dimensions and size represent valid artwork.
     * @return true if valid.
     */
    bool IsValid() const;

    /**
     * @brief Calculates aspect ratio (width / height).
     * @return Aspect ratio floating point value.
     */
    double GetAspectRatio() const;

    /**
     * @brief Formats image dimensions as 'WxH (MIME)'.
     * @return Formatted dimension string.
     */
    std::string FormatDimensions() const;

    /**
     * @brief Clears image data and zeroes dimensions.
     */
    void Clear();

    /**
     * @brief Gets image MIME type string.
     * @return Reference to MIME string.
     */
    const std::string& GetMimeType() const;

    /**
     * @brief Gets image width in pixels.
     * @return Width integer.
     */
    int GetWidth() const;

    /**
     * @brief Gets image height in pixels.
     * @return Height integer.
     */
    int GetHeight() const;

    /**
     * @brief Gets image binary data size in bytes.
     * @return Size in bytes.
     */
    size_t GetDataSizeBytes() const;

private:
    std::string mime_type_;
    int width_;
    int height_;
    size_t data_size_bytes_;
};

#endif