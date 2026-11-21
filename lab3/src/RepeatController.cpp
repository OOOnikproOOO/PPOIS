/**
 * @file RepeatController.cpp
 * @brief Implementation of RepeatController methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "RepeatController.h"

RepeatController::RepeatController(const std::string& mode, int max_repeats) :
    mode_(mode), cycle_count_(0), max_repeats_(max_repeats > 0 ? max_repeats : 10) {}

bool RepeatController::operator==(const RepeatController& other) const {
    return mode_ == other.mode_ &&
           cycle_count_ == other.cycle_count_ &&
           max_repeats_ == other.max_repeats_;
}

bool RepeatController::operator!=(const RepeatController& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const RepeatController& rc) {
    os << "Repeat[" << rc.mode_ << ", Cycle: " << rc.cycle_count_ << "/" << rc.max_repeats_ << "]";
    return os;
}

void RepeatController::CycleMode() {
    if (mode_ == "None")
        mode_ = "RepeatAll";
    else if (mode_ == "RepeatAll")
        mode_ = "RepeatOne";
    else
        mode_ = "None";

    cycle_count_ = 0;
}

void RepeatController::SetMode(const std::string& mode) {
    if (mode == "None" || mode == "RepeatOne" || mode == "RepeatAll") {
        mode_ = mode;
        cycle_count_ = 0;
    }
}

void RepeatController::IncrementCycle() {
    cycle_count_++;
}

bool RepeatController::ShouldRepeatCurrent() const {
    if (mode_ == "RepeatOne" && cycle_count_ < max_repeats_)
        return true;
    
    return false;
}

void RepeatController::Reset() {
    cycle_count_ = 0;
    mode_ = "None";
}

const std::string& RepeatController::GetMode() const {
    return mode_;
}

int RepeatController::GetCycleCount() const {
    return cycle_count_;
}

int RepeatController::GetMaxRepeats() const {
    return max_repeats_;
}