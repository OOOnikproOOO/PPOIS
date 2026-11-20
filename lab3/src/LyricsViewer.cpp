/**
 * @file LyricsViewer.cpp
 * @brief Implementation of LyricsViewer methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "LyricsViewer.h"

LyricsViewer::LyricsViewer(bool is_karaoke_mode, int font_size_pt) :
    is_karaoke_mode_(is_karaoke_mode), font_size_pt_(font_size_pt < 8 ? 8 : (font_size_pt > 48 ? 48 : font_size_pt)) {}

bool LyricsViewer::operator==(const LyricsViewer& other) const {
    return is_karaoke_mode_ == other.is_karaoke_mode_ &&
           font_size_pt_ == other.font_size_pt_ &&
           lines_ == other.lines_;
}

bool LyricsViewer::operator!=(const LyricsViewer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const LyricsViewer& viewer) {
    os << "LyricsViewer[Lines: " << viewer.lines_.size() << ", Karaoke: " << (viewer.is_karaoke_mode_ ? "ON" : "OFF") << ", Font: " << viewer.font_size_pt_ << "pt]";
    return os;
}

void LyricsViewer::AddLine(const LyricLine& line) {
    lines_.push_back(line);
}

const LyricLine* LyricsViewer::GetCurrentLine(double position_sec) const {
    const LyricLine* best_match = NULL;
    for (const auto& line : lines_) {
        if (line.GetTimestampSec() <= position_sec)
            best_match = &line;
    }

    return best_match;
}

void LyricsViewer::SetKaraokeMode(bool enable) {
    is_karaoke_mode_ = enable;
}

void LyricsViewer::SetFontSize(int font_size) {
    if (font_size < 8)
        font_size = 8;

    if (font_size > 48)
        font_size = 48;

    font_size_pt_ = font_size;
}

void LyricsViewer::Clear() {
    lines_.clear();
}

bool LyricsViewer::IsKaraokeMode() const {
    return is_karaoke_mode_;
}

int LyricsViewer::GetFontSize() const {
    return font_size_pt_;
}

size_t LyricsViewer::GetLinesCount() const {
    return lines_.size();
}

const std::vector<LyricLine>& LyricsViewer::GetLines() const {
    return lines_;
}