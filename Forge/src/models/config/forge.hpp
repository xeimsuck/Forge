#pragma once
#include <optional>
#include <models/config/version.hpp>

namespace Models {
    struct Forge {
        std::optional<Version> min_version = std::nullopt;
    };
}