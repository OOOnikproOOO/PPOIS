/**
 * @file MusicPlayer.cpp
 * @brief Implementation of MusicPlayer master coordinator methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "MusicPlayer.h"
#include <sstream>

MusicPlayer::MusicPlayer(const std::string& player_name) : player_name_(player_name), is_powered_on_(true) {}

bool MusicPlayer::operator==(const MusicPlayer& other) const {
    return player_name_ == other.player_name_ &&
           is_powered_on_ == other.is_powered_on_;
}

bool MusicPlayer::operator!=(const MusicPlayer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const MusicPlayer& player) {
    os << player.GetStatusSummary();
    return os;
}

void MusicPlayer::PowerOn() {
    is_powered_on_ = true;
}

void MusicPlayer::PowerOff() {
    is_powered_on_ = false;
    engine_.Stop();
    position_.Reset();
}

void MusicPlayer::LoadAndQueueTrack(const AudioTrack& track) {
    library_.AddTrack(track);
    queue_.Enqueue(track);
}

bool MusicPlayer::Play() {
    if (!is_powered_on_)
        return false;

    if (queue_.GetQueueSize() == 0)
        return false;

    engine_.Play();
    const AudioTrack& current = queue_.GetCurrentTrack();
    position_ = PlaybackPosition(current.GetDurationSec(), 0.0);
    history_.RecordTrack(current.GetMetadata().GetTitle());
    return true;
}

void MusicPlayer::Pause() {
    if (is_powered_on_)
        engine_.Pause();
}

void MusicPlayer::Stop() {
    engine_.Stop();
    position_.Reset();
}

bool MusicPlayer::Next() {
    bool ok = queue_.NextTrack();
    if (ok)
        Play();

    return ok;
}

bool MusicPlayer::Previous() {
    bool ok = queue_.PreviousTrack();
    if (ok)
        Play();

    return ok;
}

void MusicPlayer::Seek(double target_sec) {
    position_.SeekTo(target_sec);
}

std::string MusicPlayer::GetStatusSummary() const {
    std::ostringstream oss;
    oss << player_name_ << " [" << (is_powered_on_ ? "POWER ON" : "POWER OFF") << ", Engine: " << engine_.GetState() << ", Volume: " << volume_.GetEffectiveVolume() << "%" << ", Tracks: " << queue_.GetQueueSize() << "]";
    return oss.str();
}

bool MusicPlayer::IsPoweredOn() const {
    return is_powered_on_;
}

const std::string& MusicPlayer::GetPlayerName() const {
    return player_name_;
}

MusicLibrary& MusicPlayer::GetLibrary() {
    return library_;
}

PlaybackQueue& MusicPlayer::GetQueue() {
    return queue_;
}

AudioEngine& MusicPlayer::GetEngine() {
    return engine_;
}

AudioEffectsRack& MusicPlayer::GetEffectsRack() {
    return effects_rack_;
}

VolumeControl& MusicPlayer::GetVolume() {
    return volume_;
}

PlaybackPosition& MusicPlayer::GetPosition() {
    return position_;
}

DeviceManager& MusicPlayer::GetDeviceManager() {
    return device_manager_;
}

UserProfile& MusicPlayer::GetUser() {
    return user_;
}

SubscriptionPlan& MusicPlayer::GetSubscription() {
    return subscription_;
}

PlaybackHistory& MusicPlayer::GetHistory() {
    return history_;
}

RepeatController& MusicPlayer::GetRepeat() {
    return repeat_;
}

ShuffleEngine& MusicPlayer::GetShuffle() {
    return shuffle_;
}

SleepTimer& MusicPlayer::GetSleepTimer() {
    return sleep_timer_;
}