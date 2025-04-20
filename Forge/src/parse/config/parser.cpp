#include "parser.hpp"

namespace Parse::Config {
    Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {
    }

    auto Parser::get_tokens() -> const std::vector<Token>&{
        return tokens;
    }

    auto Parser::get_config() -> const Models::Config& {
        return config;
    }

    auto Parser::get_parse_status() -> ParseStatus {
        return parse_status;
    }


    auto Parser::parse() -> ParseStatus {
        if(parse_status!=ParseStatus::UNFINISHED) return parse_status;
        parse_status = ParseStatus::SUCCESSFUL;

        
        return get_parse_status();
    }


    auto Parser::error(const std::string& msg) -> void {
        ERROR() << msg;
        parse_status = ParseStatus::FAILED;
    }
}