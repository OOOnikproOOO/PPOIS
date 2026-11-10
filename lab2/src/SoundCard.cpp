/**
 * @file SoundCard.cpp
 * @brief Implementation of SoundCard methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SoundCard.h"
#include "Exceptions.h"

SoundCard::SoundCard(const std::string& card_model, int channel_count, const AudioDAC& dac, const AudioDSP& dsp) :
    card_model_(card_model), channel_count_(channel_count), dac_(dac), dsp_(dsp), jacks_() {}

bool SoundCard::operator==(const SoundCard& other) const {
    return (card_model_ == other.card_model_ &&
            channel_count_ == other.channel_count_ &&
            dac_ == other.dac_ &&
            dsp_ == other.dsp_ &&
            jacks_ == other.jacks_);
}

bool SoundCard::operator!=(const SoundCard& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SoundCard& card) {
    os << "SoundCard: " << card.card_model_ << " [" << card.channel_count_ << " Channels, " << card.dac_.GetSamplingRateHz() << " Hz, Jacks: " << card.jacks_.size() << "]";
    return os;
}

void SoundCard::AddJack(const AudioJack& jack) {
    jacks_.push_back(jack);
}

void SoundCard::PlayAudioStream(int sample_count, double volume_level) {
    if (sample_count <= 0)
        return;
    
    if (volume_level < 0.0 || volume_level > 1.0)
        throw ComputerException("Audio volume level must be between 0.0 and 1.0.");
    
    dac_.ConvertDigitalToAnalog(sample_count);
}

void SoundCard::ConfigureSurround(int channels) {
    if (channels != 2 && channels != 6 && channels != 8)
        throw ComputerException("Unsupported surround channel configuration: " + std::to_string(channels));
    
    channel_count_ = channels;
}

std::string SoundCard::GetCardModel() const {
    return card_model_;
}

int SoundCard::GetChannelCount() const {
    return channel_count_;
}

AudioDAC& SoundCard::GetDAC() {
    return dac_;
}

const AudioDAC& SoundCard::GetDAC() const {
    return dac_;
}

AudioDSP& SoundCard::GetDSP() {
    return dsp_;
}

const AudioDSP& SoundCard::GetDSP() const {
    return dsp_;
}

int SoundCard::GetJackCount() const {
    return static_cast<int>(jacks_.size());
}

AudioJack& SoundCard::GetJack(int index) {
    if (index < 0 || index >= static_cast<int>(jacks_.size()))
        throw DeviceNotFoundException("Audio jack index out of bounds on sound card.");
    
    return jacks_[index];
}