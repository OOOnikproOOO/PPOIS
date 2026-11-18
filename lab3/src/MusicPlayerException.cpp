/**
 * @file MusicPlayerException.cpp
 * @brief Implementation of the base MusicPlayerException class.
 * @author Nikita Momot
 * @date 2026
 */

#include "MusicPlayerException.h"

MusicPlayerException::MusicPlayerException(const std::string& message)
    : std::runtime_error(message) {}