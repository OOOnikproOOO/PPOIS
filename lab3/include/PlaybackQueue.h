/**
 * @file PlaybackQueue.h
 * @brief Declaration of the PlaybackQueue class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYBACKQUEUE_H
#define PLAYBACKQUEUE_H

#include <iostream>
#include <vector>
#include "AudioTrack.h"

/**
 * @brief Manages linear playback sequence, track navigation and dynamic queue insertion.
 */
class PlaybackQueue {
public:
    /**
     * @brief Constructs a PlaybackQueue.
     * @param max_queue_size Maximum capacity limit.
     * @param auto_advance Automatically step to next track when finished.
     */
    PlaybackQueue(size_t max_queue_size = 500, bool auto_advance = true);

    /**
     * @brief Compares two PlaybackQueue instances for equality.
     * @param other Queue to compare with.
     * @return true if index and tracks match.
     */
    bool operator==(const PlaybackQueue& other) const;

    /**
     * @brief Compares two PlaybackQueue instances for inequality.
     * @param other Queue to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PlaybackQueue& other) const;

    /**
     * @brief Stream output operator for formatting PlaybackQueue info.
     * @param os Output stream.
     * @param queue Queue instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PlaybackQueue& queue);

    /**
     * @brief Appends a track to queue tail.
     * @param track AudioTrack to insert.
     * @return true if appended.
     */
    bool Enqueue(const AudioTrack& track);

    /**
     * @brief Steps to next track in queue.
     * @return true if advanced to valid track.
     */
    bool NextTrack();

    /**
     * @brief Steps to previous track in queue.
     * @return true if stepped back.
     */
    bool PreviousTrack();

    /**
     * @brief Returns current active playing track.
     * @return Reference to AudioTrack.
     * @throws TrackNotFoundException if queue is empty.
     */
    const AudioTrack& GetCurrentTrack() const;

    /**
     * @brief Removes a track at specified index.
     * @param index Queue index.
     */
    void RemoveAt(size_t index);

    /**
     * @brief Clears entire queue and resets playback pointer.
     */
    void ClearQueue();

    /**
     * @brief Gets index of currently playing track in queue.
     * @return Zero-based track index or -1 if empty.
     */
    int GetCurrentIndex() const;

    /**
     * @brief Gets current count of tracks in queue.
     * @return Queue size.
     */
    size_t GetQueueSize() const;

    /**
     * @brief Checks if auto-advance mode is enabled.
     * @return true if auto-advance is on.
     */
    bool IsAutoAdvance() const;

    /**
     * @brief Gets constant reference to queue tracks vector.
     * @return Reference to vector of AudioTrack.
     */
    const std::vector<AudioTrack>& GetTracks() const;

private:
    int current_index_;
    std::vector<AudioTrack> tracks_;
    bool auto_advance_;
    size_t max_queue_size_;
};

#endif