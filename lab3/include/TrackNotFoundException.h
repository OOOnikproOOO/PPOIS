/**
 * @file TrackNotFoundException.h
 * @brief Declaration of TrackNotFoundException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef TRACKNOTFOUNDEXCEPTION_H
#define TRACKNOTFOUNDEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when TrackNotFoundException condition occurs.
 */
class TrackNotFoundException : public MusicPlayerException {
public:
    explicit TrackNotFoundException(const std::string& message);
};

#endif