/**
 * @file MusicPlayerException.h
 * @brief Base exception class for the music player application domain.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MUSICPLAYEREXCEPTION_H
#define MUSICPLAYEREXCEPTION_H

#include <stdexcept>
#include <string>

/**
 * @brief Base exception class for all music player domain errors.
 */
class MusicPlayerException : public std::runtime_error {
public:
    /**
     * @brief Constructs a MusicPlayerException with an explanatory message.
     * @param message Explanatory string.
     */
    explicit MusicPlayerException(const std::string& message);
};

#endif