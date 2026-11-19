/**
 * @file ShuffleEngine.h
 * @brief Declaration of the ShuffleEngine class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SHUFFLEENGINE_H
#define SHUFFLEENGINE_H

#include <iostream>
#include <vector>

/**
 * @brief Manages random track permutation without repetitions using the Fisher-Yates algorithm.
 */
class ShuffleEngine {
public:
    /**
     * @brief Constructs a ShuffleEngine.
     * @param seed Random generator seed.
     * @param is_enabled Enable shuffle mode.
     */
    ShuffleEngine(unsigned int seed = 42, bool is_enabled = false);

    /**
     * @brief Compares two ShuffleEngine instances for equality.
     * @param other Engine to compare with.
     * @return true if seed and state match.
     */
    bool operator==(const ShuffleEngine& other) const;

    /**
     * @brief Compares two ShuffleEngine instances for inequality.
     * @param other Engine to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const ShuffleEngine& other) const;

    /**
     * @brief Stream output operator for formatting ShuffleEngine info.
     * @param os Output stream.
     * @param engine Engine instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ShuffleEngine& engine);

    /**
     * @brief Generates a randomized permutation of indices [0..total_tracks-1].
     * @param total_tracks Number of tracks to shuffle.
     */
    void GenerateShuffle(size_t total_tracks);

    /**
     * @brief Retrieves shuffled track index for a given step.
     * @param step Step sequence index.
     * @return Track index in playlist.
     */
    size_t GetNextShuffledIndex(size_t step) const;

    /**
     * @brief Resets shuffle order and history.
     */
    void Reset();

    /**
     * @brief Toggles shuffle mode.
     * @param enable Flag.
     */
    void ToggleShuffle(bool enable);

    /**
     * @brief Gets random generator seed.
     * @return Seed integer.
     */
    unsigned int GetSeed() const;

    /**
     * @brief Checks if shuffle mode is enabled.
     * @return true if enabled.
     */
    bool IsEnabled() const;

    /**
     * @brief Gets count of elements in current shuffled permutation.
     * @return Size of shuffled list.
     */
    size_t GetShuffledSize() const;

    /**
     * @brief Gets constant reference to shuffled order indices.
     * @return Reference to vector of size_t indices.
     */
    const std::vector<size_t>& GetShuffledOrder() const;

private:
    unsigned int seed_;
    bool is_enabled_;
    std::vector<size_t> shuffled_order_;
};

#endif