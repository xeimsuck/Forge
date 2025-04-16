#pragma once
#include <stdexcept>
#include <string>
#include <expected>

namespace File {
    class FileReader {
    public:
        auto read(const std::string& path) -> std::expected<std::string, std::runtime_error>;
    };

    auto read_file(const std::string& path) -> std::expected<std::string, std::runtime_error>;
}