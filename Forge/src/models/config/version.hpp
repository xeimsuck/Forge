#pragma once
#include <cstdint>
#include <string>

namespace Models {
    struct Version {
        explicit Version(uint8_t major = 0, uint8_t minor = 0, uint8_t patch = 0);

        explicit Version(const std::string& str);

        uint8_t major = 0;
        uint8_t minor = 0;
        uint8_t patch = 0;
    };
}