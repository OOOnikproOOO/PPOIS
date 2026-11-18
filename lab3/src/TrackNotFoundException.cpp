/**
 * @file TrackNotFoundException.cpp
 * @brief Implementation of TrackNotFoundException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "TrackNotFoundException.h"

TrackNotFoundException::TrackNotFoundException(const std::string& message)
    : MusicPlayerException(message) {}