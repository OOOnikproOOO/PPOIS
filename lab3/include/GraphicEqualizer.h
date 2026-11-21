/**
 * @file GraphicEqualizer.h
 * @brief Declaration of the GraphicEqualizer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef GRAPHICEQUALIZER_H
#define GRAPHICEQUALIZER_H

#include <iostream>
#include <string>
#include <vector>
#include "EqualizerBand.h"

/**
 * @brief Multi-band graphic equalizer with preamp gain and musical genre presets.
 */
class GraphicEqualizer {
public:
    /**
     * @brief Constructs a 10-band GraphicEqualizer.
     * @param preset_name Active preset name.
     * @param preamp_gain_db Preamp level in decibels.
     * @param is_active Processing toggle.
     */
    GraphicEqualizer(const std::string& preset_name = "Flat", double preamp_gain_db = 0.0, bool is_active = true);

    /**
     * @brief Compares two GraphicEqualizer instances for equality.
     * @param other Equalizer to compare with.
     * @return true if presets and bands match.
     */
    bool operator==(const GraphicEqualizer& other) const;

    /**
     * @brief Compares two GraphicEqualizer instances for inequality.
     * @param other Equalizer to compare with.
     * @return true if presets or bands differ.
     */
    bool operator!=(const GraphicEqualizer& other) const;

    /**
     * @brief Stream output operator for formatting GraphicEqualizer info.
     * @param os Output stream.
     * @param eq Equalizer instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const GraphicEqualizer& eq);

    /**
     * @brief Loads standard EQ curve ("Rock", "Pop", "Jazz", "Classical", "Flat").
     * @param preset Name of preset.
     */
    void ApplyPreset(const std::string& preset);

    /**
     * @brief Sets gain for a specific band index.
     * @param band_index Zero-based band index.
     * @param gain Gain in dB.
     */
    void SetBandGain(size_t band_index, double gain);

    /**
     * @brief Resets all bands to 0 dB flat response.
     */
    void ResetAllBands();

    /**
     * @brief Toggles equalizer on or off.
     * @param active State.
     */
    void ToggleEqualizer(bool active);

    /**
     * @brief Gets reference to an individual frequency band.
     * @param index Band index.
     * @return Const reference to EqualizerBand.
     */
    const EqualizerBand& GetBand(size_t index) const;

    /**
     * @brief Gets count of equalizer bands.
     * @return Band count.
     */
    size_t GetBandsCount() const;

    /**
     * @brief Gets name of active EQ preset.
     * @return Reference to preset name string.
     */
    const std::string& GetPresetName() const;

    /**
     * @brief Gets preamp gain in decibels.
     * @return Preamp gain in dB.
     */
    double GetPreampGainDb() const;

    /**
     * @brief Checks if equalizer processing is active.
     * @return true if active.
     */
    bool IsActive() const;

private:
    std::string preset_name_;
    double preamp_gain_db_;
    bool is_active_;
    std::vector<EqualizerBand> bands_;
};

#endif