#include <vector>
#include <models/config/config.hpp>
#include <logger/logger.hpp>
#include <parse/config/token.hpp>

namespace Parse::Config {
    class Parser {
        enum class ParseStatus {
            UNFINISHED,
            SUCCESSFUL,
            FAILED
        };

    public:
        explicit Parser(const std::vector<Token>& tokens);
        auto parse() -> ParseStatus;

        auto get_parse_status() -> ParseStatus;
        auto get_tokens() -> const std::vector<Token>&;
        auto get_config() -> const Models::Config&;

    private:
        auto error(const std::string& msg) -> void;

        const std::vector<Token>& tokens;
        Models::Config config;
        ParseStatus parse_status;
    };
}