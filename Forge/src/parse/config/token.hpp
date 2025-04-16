
#pragma once
#include <cstdint>
#include <string>

namespace Parse::Config {
    struct Token {
        enum class TokenType {
            LEFT_BRACKETS, RIGHT_BRACKETS, COMMON, EQUAL,

            SECTION, IDENTIFIER,

            STRING, NUMBER,

            END_OF_FILE
        };

        TokenType type = TokenType::END_OF_FILE;
        std::string literal;
        uint32_t line = 0;
    };
}