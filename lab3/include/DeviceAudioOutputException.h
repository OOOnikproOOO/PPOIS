/**
 * @file DeviceAudioOutputException.h
 * @brief Declaration of DeviceAudioOutputException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef DEVICEAUDIOOUTPUTEXCEPTION_H
#define DEVICEAUDIOOUTPUTEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when DeviceAudioOutputException condition occurs.
 */
class DeviceAudioOutputException : public MusicPlayerException {
public:
    explicit DeviceAudioOutputException(const std::string& message);
};

#endif