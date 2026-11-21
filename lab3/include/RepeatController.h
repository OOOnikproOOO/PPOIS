/**
 * @file RepeatController.h
 * @brief Declaration of the RepeatController class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef REPEATCONTROLLER_H
#define REPEATCONTROLLER_H

#include <iostream>
#include <string>

/**
 * @brief Manages playback looping modes ("None", "RepeatOne", "RepeatAll") and cycle counts.
 */
class RepeatController {
public:
    /**
     * @brief Constructs a RepeatController.
     * @param mode Active repeat mode.
     * @param max_repeats Maximum loops allowed.
     */
    RepeatController(const std::string& mode = "None", int max_repeats = 100);

    /**
     * @brief Compares two RepeatController instances for equality.
     * @param other Controller to compare with.
     * @return true if mode and repeats match.
     */
    bool operator==(const RepeatController& other) const;

    /**
     * @brief Compares two RepeatController instances for inequality.
     * @param other Controller to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const RepeatController& other) const;

    /**
     * @brief Stream output operator for formatting RepeatController info.
     * @param os Output stream.
     * @param rc Controller instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const RepeatController& rc);

    /**
     * @brief Cycles mode between None -> RepeatAll -> RepeatOne -> None.
     */
    void CycleMode();

    /**
     * @brief Explicitly sets repeat mode.
     * @param mode Target mode string.
     */
    void SetMode(const std::string& mode);

    /**
     * @brief Increments current repetition cycle counter.
     */
    void IncrementCycle();

    /**
     * @brief Determines whether the current track should be replayed.
     * @return true if repeat-one is active and under limit.
     */
    bool ShouldRepeatCurrent() const;

    /**
     * @brief Resets cycle counter to zero.
     */
    void Reset();

    /**
     * @brief Gets current active repeat mode ("None", "RepeatAll", "RepeatOne").
     * @return Reference to mode string.
     */
    const std::string& GetMode() const;

    /**
     * @brief Gets number of completed repeat cycles.
     * @return Cycle count.
     */
    int GetCycleCount() const;

    /**
     * @brief Gets maximum repeat limit threshold.
     * @return Max repeats integer.
     */
    int GetMaxRepeats() const;

private:
    std::string mode_;
    int cycle_count_;
    int max_repeats_;
};

#endif