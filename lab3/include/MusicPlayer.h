/**
 * @file MusicPlayer.h
 * @brief Declaration of the MusicPlayer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <iostream>
#include <string>
#include "MusicLibrary.h"
#include "PlaybackQueue.h"
#include "AudioEngine.h"
#include "AudioEffectsRack.h"
#include "VolumeControl.h"
#include "PlaybackPosition.h"
#include "RepeatController.h"
#include "ShuffleEngine.h"
#include "PlaybackHistory.h"
#include "DeviceManager.h"
#include "UserProfile.h"
#include "SubscriptionPlan.h"
#include "SleepTimer.h"

/**
 * @brief Master facade orchestrator coordinating media library, audio engine, queue, effects and devices.
 */
class MusicPlayer {
public:
    /**
     * @brief Constructs a MusicPlayer instance.
     * @param player_name Commercial player brand name.
     */
    explicit MusicPlayer(const std::string& player_name = "Audi Music Player");

    /**
     * @brief Compares two MusicPlayer instances for equality.
     * @param other Player to compare with.
     * @return true if player name and power state match.
     */
    bool operator==(const MusicPlayer& other) const;

    /**
     * @brief Compares two MusicPlayer instances for inequality.
     * @param other Player to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const MusicPlayer& other) const;

    /**
     * @brief Stream output operator for formatting MusicPlayer info.
     * @param os Output stream.
     * @param player Player instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const MusicPlayer& player);

    /**
     * @brief Powers on music player hardware and audio subsystem.
     */
    void PowerOn();

    /**
     * @brief Powers down player, halts audio engine and clears queue.
     */
    void PowerOff();

    /**
     * @brief Loads a track into media library and appends it to active playback queue.
     * @param track AudioTrack to load.
     */
    void LoadAndQueueTrack(const AudioTrack& track);

    /**
     * @brief Starts playback of current track in queue.
     * @return true if playback initiated.
     */
    bool Play();

    /**
     * @brief Pauses audio playback retaining buffer position.
     */
    void Pause();

    /**
     * @brief Halts playback and rewinds track position.
     */
    void Stop();

    /**
     * @brief Skips forward to next track in queue.
     * @return true if stepped forward.
     */
    bool Next();

    /**
     * @brief Skips back to previous track in queue.
     * @return true if stepped back.
     */
    bool Previous();

    /**
     * @brief Seeks active track timeline to target timestamp in seconds.
     * @param target_sec Seconds offset.
     */
    void Seek(double target_sec);

    /**
     * @brief Formats real-time playback dashboard status summary.
     * @return Status string.
     */
    std::string GetStatusSummary() const;

    /**
     * @brief Checks if player power is on.
     * @return true if powered on.
     */
    bool IsPoweredOn() const;

    /**
     * @brief Gets player commercial name.
     * @return Reference to player name string.
     */
    const std::string& GetPlayerName() const;

    /**
     * @brief Gets mutable reference to MusicLibrary.
     * @return Reference to MusicLibrary.
     */
    MusicLibrary& GetLibrary();

    /**
     * @brief Gets mutable reference to PlaybackQueue.
     * @return Reference to PlaybackQueue.
     */
    PlaybackQueue& GetQueue();

    /**
     * @brief Gets mutable reference to AudioEngine.
     * @return Reference to AudioEngine.
     */
    AudioEngine& GetEngine();

    /**
     * @brief Gets mutable reference to AudioEffectsRack.
     * @return Reference to AudioEffectsRack.
     */
    AudioEffectsRack& GetEffectsRack();

    /**
     * @brief Gets mutable reference to VolumeControl.
     * @return Reference to VolumeControl.
     */
    VolumeControl& GetVolume();

    /**
     * @brief Gets mutable reference to PlaybackPosition.
     * @return Reference to PlaybackPosition.
     */
    PlaybackPosition& GetPosition();

    /**
     * @brief Gets mutable reference to DeviceManager.
     * @return Reference to DeviceManager.
     */
    DeviceManager& GetDeviceManager();

    /**
     * @brief Gets mutable reference to UserProfile.
     * @return Reference to UserProfile.
     */
    UserProfile& GetUser();

    /**
     * @brief Gets mutable reference to SubscriptionPlan.
     * @return Reference to SubscriptionPlan.
     */
    SubscriptionPlan& GetSubscription();

    /**
     * @brief Gets mutable reference to PlaybackHistory.
     * @return Reference to PlaybackHistory.
     */
    PlaybackHistory& GetHistory();

    /**
     * @brief Gets mutable reference to RepeatController.
     * @return Reference to RepeatController.
     */
    RepeatController& GetRepeat();

    /**
     * @brief Gets mutable reference to ShuffleEngine.
     * @return Reference to ShuffleEngine.
     */
    ShuffleEngine& GetShuffle();

    /**
     * @brief Gets mutable reference to SleepTimer.
     * @return Reference to SleepTimer.
     */
    SleepTimer& GetSleepTimer();

private:
    std::string player_name_;
    bool is_powered_on_;
    MusicLibrary library_;
    PlaybackQueue queue_;
    AudioEngine engine_;
    AudioEffectsRack effects_rack_;
    VolumeControl volume_;
    PlaybackPosition position_;
    RepeatController repeat_;
    ShuffleEngine shuffle_;
    PlaybackHistory history_;
    DeviceManager device_manager_;
    UserProfile user_;
    SubscriptionPlan subscription_;
    SleepTimer sleep_timer_;
};

#endif