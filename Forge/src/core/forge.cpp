#include <core/forge.hpp>
#include <logger/logger.hpp>
#include <file/file_reader.hpp>
#include <filesystem>
#include <parse/config/scanner.hpp>
#include <parse/config/parser.hpp>

using namespace Parse::Config;

Forge& Forge::init(){
    static Forge instance;
    return instance;
}

int Forge::run(int argc, char** argv){
    DEBUG() << "Run Forge::run";

    if(argc!=1) {
        INFO() << "Usage: forge";
        return -1;
    }


    std::string path_to_config = std::string(std::filesystem::current_path()) + "/forge.toml";
    auto src = File::read_file(path_to_config);
    if(!src.has_value()){
        ERROR() << "[ERROR]" << src.error().what();
        return 1;
    }


    Scanner scanner(src.value());
    INFO() << "Scanning is started successfully";
    if(scanner.scan()!=Scanner::ScanStatus::SUCCESSFUL){
        ERROR() << "[ERROR] Config scanning is failed";
        return 1;
    }
    INFO() << "Scanning is finished successfully";

    
    Parser parser(scanner.get_tokens());
    INFO() << "Parsing is started";
    if(parser.parse()!=Parser::ParseStatus::SUCCESSFUL){
        ERROR() << "[ERROR] Config parsing is failed";
        return 1;
    }
    INFO() << "Parsing is finished successfully";



    DEBUG() << "End Forge::run";
    return 0;
}