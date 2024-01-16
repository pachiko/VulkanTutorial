#pragma once
#include <optional>
#include "application.h"


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily; // Implicitly supports memory transfers
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};