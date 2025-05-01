#pragma once
#include <models/config/forge.hpp>
#include <models/config/project.hpp>

namespace Models {
    struct Config {
        Forge forge;
        Project project;
    };
}