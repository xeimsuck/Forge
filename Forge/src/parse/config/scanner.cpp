#include "scanner.hpp"
#include "parse/config/token.hpp"
#include <cctype>
#include <format>
#include <logger/logger.hpp>

namespace Parse::Config {
    using enum Token::TokenType;

    Scanner::Scanner(const std::string& src) : src(src) {
    }

    auto Scanner::scan() -> ScanStatus {
        if(scan_status != ScanStatus::UNFINISHED) return scan_status;

        scan_status = ScanStatus::SUCCESSFUL;

        while(!is_at_end()){
            scan_once();
            start = current;
        }
        tokens.emplace_back(Token::TokenType::END_OF_FILE, "", line);

        return scan_status;
    }

    auto Scanner::get_tokens() -> const std::vector<Token>& {
        return tokens;
    }

    auto Scanner::get_src() -> const std::string& {
        return src;
    }

    auto Scanner::get_scan_status() -> ScanStatus {
        return scan_status;
    }



    auto Scanner::scan_once() -> void {
        auto sym = advance();

        switch (sym) {
            case ',': add_token(COMMON); break;
            case '=': add_token(EQUAL); break;
            case '[': section(); break;
            case ' ':
            case '\t':
            case '\r': break;
            case '\n': ++line; break;
            case '\"': string(); break;
            default:
                if(isdigit(sym)) number();
                else if(isalpha(sym)) identifier();
                else error(std::format("Unresolved symbol: {}", sym));
                break;
        }
    }

    auto Scanner::add_token(Token::TokenType token_type, std::string literal, int line) -> void {
        tokens.emplace_back(token_type, std::move(literal), line);
    }


    auto Scanner::is_alpha(int sym) -> bool {
        return isalpha(sym) || sym=='_';
    }

    auto Scanner::is_digit(int sym) -> bool {
        return is_digit(sym);
    }


    auto Scanner::is_at_end() -> bool {
        return current>=src.size();
    }

    auto Scanner::advance() -> char {
        return is_at_end() ? '\0' : src[current++];
    }

    auto Scanner::peek() -> char {
        return is_at_end() ? '\0' : src[current];
    }



    auto Scanner::section() -> void {
        std::string value;
        while (!is_at_end() && isalpha(peek())!=0) {
            value.push_back(advance());
        }

        if(advance()!=']') {
            error(std::format("Unterminated section at line {}", line));
            return;
        }

        tokens.push_back( Token(Token::TokenType::SECTION, value, line));
    }

    auto Scanner::identifier() -> void {
        while (is_alpha(peek())) advance();

        const auto literal = src.substr(start, current-start);
        add_token(IDENTIFIER, std::move(literal), line);
    }

    auto Scanner::string() -> void {
        std::string value;
        while (!is_at_end() && peek()!='\"') {
            value.push_back(advance());
        }

        if(advance()!='\"') {
            error(std::format("Unterminated string at line {}", line));
            return;
        }
        
        add_token(SECTION, value, line);
    }

    auto Scanner::number() -> void {
        while (is_digit(peek())) advance();

        const auto literal = src.substr(start, current-start);
        add_token(NUMBER, std::move(literal), line);
    }



    auto Scanner::error(const std::string& msg) -> void {
        ERROR() << msg;
        scan_status = ScanStatus::FAILED;
    }
}