/**
 * @file AlbumArt.cpp
 * @brief Implementation of AlbumArt methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AlbumArt.h"
#include <sstream>

AlbumArt::AlbumArt(const std::string& mime_type, int width, int height, size_t data_size_bytes) :
    mime_type_(mime_type), width_(width < 0 ? 0 : width), height_(height < 0 ? 0 : height), data_size_bytes_(data_size_bytes) {}

bool AlbumArt::operator==(const AlbumArt& other) const {
    return mime_type_ == other.mime_type_ &&
           width_ == other.width_ &&
           height_ == other.height_ &&
           data_size_bytes_ == other.data_size_bytes_;
}

bool AlbumArt::operator!=(const AlbumArt& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AlbumArt& art) {
    os << "AlbumArt[" << art.FormatDimensions() << ", " << (art.data_size_bytes_ / 1024) << " KB]";
    return os;
}

bool AlbumArt::IsValid() const {
    return width_ > 0 && height_ > 0 && data_size_bytes_ > 0;
}

double AlbumArt::GetAspectRatio() const {
    if (height_ <= 0)
        return 0.0;

    return static_cast<double>(width_) / height_;
}

std::string AlbumArt::FormatDimensions() const {
    std::ostringstream oss;
    oss << width_ << "x" << height_ << " (" << mime_type_ << ")";
    return oss.str();
}

void AlbumArt::Clear() {
    width_ = 0;
    height_ = 0;
    data_size_bytes_ = 0;
}

const std::string& AlbumArt::GetMimeType() const {
    return mime_type_;
}

int AlbumArt::GetWidth() const {
    return width_;
}

int AlbumArt::GetHeight() const {
    return height_;
}

size_t AlbumArt::GetDataSizeBytes() const {
    return data_size_bytes_;
}