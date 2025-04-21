#include <vector>
#include <models/config/config.hpp>
#include <logger/logger.hpp>
#include <parse/config/token.hpp>
#include <unordered_map>

namespace Parse::Config {
    class Parser {
    public:
        enum class ParseStatus {
            UNFINISHED,
            SUCCESSFUL,
            FAILED
        };

        explicit Parser(const std::vector<Token>& tokens);
        auto parse() -> ParseStatus;

        auto get_parse_status() -> ParseStatus;
        auto get_tokens() -> const std::vector<Token>&;
        auto get_config() -> const Models::Config&;

    private:
        auto synchronize() -> void;

        auto is_at_end() -> bool;
        auto peek() -> const Token&;
        auto advance() -> const Token&;
        auto next() -> const Token&;

        auto parse_forge() -> void;
        auto parse_project() -> void;
        
        auto error(const std::string& msg) -> void;

    private:
        const std::vector<Token>& tokens;
        Models::Config config;
        ParseStatus parse_status = ParseStatus::UNFINISHED;
        int current = 0;

        const std::unordered_map<std::string, void(Parser::*)()> literal2method{
            {"forge", &Parser::parse_forge},
            {"project", &Parser::parse_project}
        };
    };
}