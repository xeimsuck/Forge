#include "file_reader.hpp"
#include <fstream>

namespace File {
    auto FileReader::read(const std::string& path) -> std::expected<std::string, std::runtime_error> {
        std::ifstream file(path);
        if(!file) {
            return std::unexpected(
                std::runtime_error(std::format("Can`t open file {}", path))
            );        
        }

        std::string src, line;
        while (std::getline(file, line)) {
            if(!src.empty()) src.push_back('\n');
            src+=line;
        }

        return std::move(src);
    }

    auto read_file(const std::string& path) -> std::expected<std::string, std::runtime_error> {
        FileReader file_reader;
        return file_reader.read(path);
    }
}