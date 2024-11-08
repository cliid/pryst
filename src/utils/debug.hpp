#pragma once
#include "logger.hpp"

#define PRYST_DEBUG(msg) \
    if (pryst::Logger::getInstance().isDebugEnabled()) { \
        pryst::Logger::getInstance().debug(msg); \
    }

#define PRYST_ERROR(msg) pryst::Logger::getInstance().error(msg)
#define PRYST_INFO(msg) pryst::Logger::getInstance().info(msg)
#define PRYST_DEBUG_FUNC_ENTRY() PRYST_DEBUG("Entering " + std::string(__FUNCTION__))
#define PRYST_DEBUG_FUNC_EXIT() PRYST_DEBUG("Exiting " + std::string(__FUNCTION__))
