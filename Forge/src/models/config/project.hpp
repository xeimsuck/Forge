#pragma once
#include <optional>
#include <models/config/version.hpp>
#include <string>

namespace Models {
    struct Project {
        std::string name;
        std::optional<Version> version;
        std::string source_dir = "dist/build";
        std::string build_dir = "dist/debug";
        std::string standard = "17";
    };
}