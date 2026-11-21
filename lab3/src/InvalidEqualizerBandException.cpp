/**
 * @file InvalidEqualizerBandException.cpp
 * @brief Implementation of InvalidEqualizerBandException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "InvalidEqualizerBandException.h"

InvalidEqualizerBandException::InvalidEqualizerBandException(const std::string& message)
    : MusicPlayerException(message) {}