#include "parser.hpp"
#include "logger/logger.hpp"
#include "models/config/project.hpp"
#include "models/config/version.hpp"
#include "parse/config/token.hpp"
#include <format>
#include <utilite/utilite.hpp>

namespace Parse::Config {
    using enum Token::TokenType;

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

        while (!is_at_end()) {
            const auto& token = advance();

            if(token.type!=SECTION){
                error(std::format("There is should be section on line {}", token.line));
                synchronize();
                continue;
            }

            auto section_method = literal2method.find(Utilite::to_lower(token.literal));
            if(section_method==literal2method.end()){
                error(std::format("Unknown section \"{}\"", token.literal));
                synchronize();
                continue;
            }

            (this->*(section_method->second))();
        }
        
        return get_parse_status();
    }


    auto Parser::synchronize() -> void {
        while (!is_at_end() && peek().type!=SECTION) {
            ++current;
        }
    }

    auto Parser::error(const std::string& msg) -> void {
        ERROR() << "[ERROR] " << msg;
        parse_status = ParseStatus::FAILED;
    }

    auto Parser::is_at_end() -> bool {
        return current>=tokens.size() || peek().type==END_OF_FILE;
    }

    auto Parser::peek() -> const Token& {
        return tokens[current];
    }

    auto Parser::advance() -> const Token& {
        return  tokens[current++];
    }

    auto Parser::next() -> const Token& {
        return tokens[current+1];
    }

    auto Parser::parse_forge() -> void {
        DEBUG() << "Start parse forge section";
        while (!is_at_end()) {
            if(peek().type==SECTION) break;

            auto& token = advance();
            if(advance().type!=EQUAL) {
                error(std::format("[ERROR] Missed \'=\' after indentifier at line {}", next().line));
                continue;
            }

            auto& value = advance();
            if(token.literal=="min_version"){
                DEBUG() << "Parsing min_version";
                config.forge.min_version = Models::Version(value.literal);
            } else {
                error(std::format("[ERROR] Unknown parameter {} at the line {}", token.literal, token.line));
            }
        }
        DEBUG() << "Finish parse forge section";
    }

    auto Parser::parse_project() -> void {
        DEBUG() << "Start parse project section";
        while (!is_at_end()) {
            if(peek().type==SECTION) break;

            auto& token = advance();
            if(advance().type!=EQUAL) {
                error(std::format("[ERROR] Missed \'=\' after indentifier at line {}", next().line));
                continue;
            }

            auto& value = advance();
            if(token.literal=="name"){
                DEBUG() << "Parsing name";
                config.project.name = value.literal;
            } else if(token.literal=="version") {
                DEBUG() << "Parsing version";
                config.project.version = Models::Version(value.literal);
            } else if(token.literal=="source_dir") {
                DEBUG() << "Parsing source_dir";
                config.project.source_dir = value.literal;
            }  else if(token.literal=="build_dir"){
                DEBUG() << "Parsing build_dir";
                config.project.build_dir = value.literal;
            } else if(token.literal=="standard"){
                DEBUG() << "Parsing standard";
                config.project.standard = value.literal;
            } else {
                error(std::format("[ERROR] Unknown parameter {} at the line {}", token.literal, token.line));
            }
        }
        DEBUG() << "Finish parse project section";
    }
}