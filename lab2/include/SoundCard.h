/**
 * @file SoundCard.h
 * @brief Declaration of the SoundCard class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <iostream>
#include <string>
#include <vector>
#include "AudioDAC.h"
#include "AudioDSP.h"
#include "AudioJack.h"

/**
 * @brief Class modeling an audio sound card uniting AudioDAC, AudioDSP, and AudioJacks.
 */
class SoundCard {
public:
    /**
     * @brief Constructs a sound card with specified model, DAC and DSP.
     * @param card_model Commercial device name.
     * @param channel_count Output channel count (2 - for Stereo, 6 - for 5.1, 8 - for 7.1).
     * @param dac Digital-to-analog audio converter.
     * @param dsp Digital signal processor.
     */
    explicit SoundCard(const std::string& card_model = "Creative Sound BlasterX AE-5", int channel_count = 6, const AudioDAC& dac = AudioDAC(96000, 24, 122.0), const AudioDSP& dsp = AudioDSP("Gaming Surround", 1, 0.0));

    /**
     * @brief Compares two sound cards for equality.
     * @param other SoundCard to compare with.
     * @return true if properties match.
     */
    bool operator==(const SoundCard& other) const;

    /**
     * @brief Inequality operator.
     * @param other SoundCard to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const SoundCard& other) const;

    /**
     * @brief Stream output operator for formatting sound card state.
     * @param os Output stream.
     * @param card SoundCard instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SoundCard& card);

    /**
     * @brief Adds an audio jack connector to the sound card back panel.
     * @param jack AudioJack instance to install.
     */
    void AddJack(const AudioJack& jack);

    /**
     * @brief Plays an audio sound stream through DAC and DSP units.
     * @param sample_count Number of digital samples to process.
     * @param volume_level Master output volume level (0.0 to 1.0).
     */
    void PlayAudioStream(int sample_count, double volume_level);

    /**
     * @brief Configures multichannel surround output mode.
     * @param channels Target channel count (2, 6, 8).
     */
    void ConfigureSurround(int channels);

    /**
     * @brief Gets sound card commercial model name.
     * @return Model name string.
     */
    std::string GetCardModel() const;

    /**
     * @brief Gets current audio channel count.
     * @return Channel count.
     */
    int GetChannelCount() const;

    /**
     * @brief Gets reference to the internal AudioDAC unit.
     * @return Reference to AudioDAC.
     */
    AudioDAC& GetDAC();
    const AudioDAC& GetDAC() const;

    /**
     * @brief Gets reference to the internal AudioDSP coprocessor.
     * @return Reference to AudioDSP.
     */
    AudioDSP& GetDSP();
    const AudioDSP& GetDSP() const;

    /**
     * @brief Gets count of installed physical audio jacks.
     * @return Jack count.
     */
    int GetJackCount() const;

    /**
     * @brief Gets reference to audio jack at specified index.
     * @param index Jack index.
     * @return Reference to AudioJack.
     */
    AudioJack& GetJack(int index);

private:
    std::string card_model_;
    int channel_count_;
    AudioDAC dac_;
    AudioDSP dsp_;
    std::vector<AudioJack> jacks_;
};

#endif