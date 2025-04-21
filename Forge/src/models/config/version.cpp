#include "version.hpp"
#include <logger/logger.hpp>

namespace Models {
    Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
        : major(major), minor(minor), patch(patch){
    }

    Version::Version(const std::string& str){
        int current = 0;

        auto parse = [&current, &str](uint8_t& n) -> bool {
            if(current<=str.size() && !isdigit(str[current])) {
                return false;
            }

            while(current<=str.size() && isdigit(str[current])){
                n=n*10+(str[current++]-'0');
            }
            ++current;

            return true;
        };

        if(!parse(this->major)){
            ERROR() << "[ERROR] Incorrect major version";
        } else if(!parse(this->minor)){
            ERROR() << "[ERROR] Incorrect minor version";
        } else if(!parse(this->patch)){
            ERROR() << "[ERROR] Incorrect patch version";
        }
    }
}