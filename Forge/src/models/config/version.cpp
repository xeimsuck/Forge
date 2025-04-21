#include "version.hpp"
#include <logger/logger.hpp>

namespace Models {
    Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
        : major(major), minor(minor), patch(patch){
    }

    Version::Version(const std::string& str){
        int current = 0;

        auto parse = [&current, &str](uint8_t n){
            if(current<=str.size() && !isdigit(str[current])) {
                ERROR() << "[ERROR] Incorrect version";
                return;
            }

            while(current<=str.size() && isdigit(str[current])){
                n=n*10+(str[current]-'0');
                ++current;
            }
        };

        parse(this->major);
        parse(this->minor);
        parse(this->patch);
    }
}