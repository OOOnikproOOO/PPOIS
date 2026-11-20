/**
 * @file LyricsViewer.h
 * @brief Declaration of the LyricsViewer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef LYRICSVIEWER_H
#define LYRICSVIEWER_H

#include <iostream>
#include <string>
#include <vector>
#include "LyricLine.h"

/**
 * @brief Manages synchronized song lyrics presentation, karaoke mode and time-based line lookup.
 */
class LyricsViewer {
public:
    /**
     * @brief Constructs a LyricsViewer.
     * @param is_karaoke_mode Karaoke highlighting toggle.
     * @param font_size_pt Display font point size (8 to 48).
     */
    LyricsViewer(bool is_karaoke_mode = true, int font_size_pt = 16);

    /**
     * @brief Compares two LyricsViewer instances for equality.
     * @param other Viewer to compare with.
     * @return true if properties and lines match.
     */
    bool operator==(const LyricsViewer& other) const;

    /**
     * @brief Compares two LyricsViewer instances for inequality.
     * @param other Viewer to compare with.
     * @return true if properties or lines differ.
     */
    bool operator!=(const LyricsViewer& other) const;

    /**
     * @brief Stream output operator for formatting LyricsViewer info.
     * @param os Output stream.
     * @param viewer Viewer instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const LyricsViewer& viewer);

    /**
     * @brief Appends a synchronized lyric line to the song text.
     * @param line LyricLine instance to insert.
     */
    void AddLine(const LyricLine& line);

    /**
     * @brief Finds currently active line for a playback timestamp.
     * @param position_sec Current song timestamp in seconds.
     * @return Pointer to active LyricLine, or nullptr if none.
     */
    const LyricLine* GetCurrentLine(double position_sec) const;

    /**
     * @brief Toggles karaoke visual mode.
     * @param enable Status flag.
     */
    void SetKaraokeMode(bool enable);

    /**
     * @brief Sets display font size with boundary clamping.
     * @param font_size Point size (8 to 48).
     */
    void SetFontSize(int font_size);

    /**
     * @brief Clears all lyric lines from viewer.
     */
    void Clear();

    /**
     * @brief Checks if karaoke mode is enabled.
     * @return true if karaoke is active.
     */
    bool IsKaraokeMode() const;

    /**
     * @brief Gets display font size in points.
     * @return Font size.
     */
    int GetFontSize() const;

    /**
     * @brief Gets total count of loaded lyric lines.
     * @return Lines count.
     */
    size_t GetLinesCount() const;

    /**
     * @brief Gets constant reference to all stored lyric lines.
     * @return Reference to vector of LyricLine.
     */
    const std::vector<LyricLine>& GetLines() const;

private:
    bool is_karaoke_mode_;
    int font_size_pt_;
    std::vector<LyricLine> lines_;
};

#endif