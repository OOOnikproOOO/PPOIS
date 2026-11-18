/**
 * @file DeviceAudioOutputException.cpp
 * @brief Implementation of DeviceAudioOutputException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "DeviceAudioOutputException.h"

DeviceAudioOutputException::DeviceAudioOutputException(const std::string& message)
    : MusicPlayerException(message) {}