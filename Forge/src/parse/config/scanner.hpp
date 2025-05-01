#pragma once
#include <cstdint>
#include <parse/config/token.hpp>
#include <string>
#include <expected>
#include <vector>

namespace Parse::Config {
    class Scanner {
    public:
        enum class ScanStatus {
            UNFINISHED,
            SUCCESSFUL,
            FAILED
        };

        explicit Scanner(const std::string& src);
        auto scan() -> ScanStatus;
        auto get_tokens() -> const std::vector<Token>&;
        auto get_src() -> const std::string&;
        auto get_scan_status() -> ScanStatus;

    private:
        auto scan_once() -> void;
        auto add_token(Token::TokenType token_type, std::string literal = "", int line = 0) -> void;

        auto is_alpha(int sym) -> bool;
        auto is_digit(int sym) -> bool;

        auto is_at_end() -> bool;
        auto advance() -> char;
        auto peek() -> char;

        auto section() -> void;
        auto identifier() -> void;
        auto string() -> void;
        auto number() -> void;

        auto error(const std::string& msg) -> void;

        uint32_t start = 0, current = 0, line = 1;
        const std::string& src;
        std::vector<Token> tokens;
        ScanStatus scan_status = ScanStatus::UNFINISHED;        
    };
}