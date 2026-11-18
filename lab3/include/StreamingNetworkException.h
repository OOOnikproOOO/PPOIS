/**
 * @file StreamingNetworkException.h
 * @brief Declaration of StreamingNetworkException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef STREAMINGNETWORKEXCEPTION_H
#define STREAMINGNETWORKEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when StreamingNetworkException condition occurs.
 */
class StreamingNetworkException : public MusicPlayerException {
public:
    explicit StreamingNetworkException(const std::string& message);
};

#endif