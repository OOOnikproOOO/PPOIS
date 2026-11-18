/**
 * @file StreamingNetworkException.cpp
 * @brief Implementation of StreamingNetworkException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "StreamingNetworkException.h"

StreamingNetworkException::StreamingNetworkException(const std::string& message)
    : MusicPlayerException(message) {}