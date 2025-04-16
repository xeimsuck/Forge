#include <core/forge.hpp>
#include <logger/logger.hpp>
#include <file/file_reader.hpp>
#include <parse/config/scanner.hpp>
#include <filesystem>

using namespace Parse::Config;

Forge& Forge::init(){
    static Forge instance;
    return instance;
}

int Forge::run(int argc, char** argv){
    DEBUG() << "Run Forge::run";

    if(argc!=1) {
        FATAL() << "Usage: forge";
        return 1;
    }


    std::string path_to_config = std::string(std::filesystem::current_path()) + "/forge.toml";
    auto src = File::read_file(path_to_config);
    if(!src.has_value()){
        ERROR() << src.error().what();
        return 1;
    }


    Scanner scanner(src.value());
    DEBUG() << "Scan is started";
    if(scanner.scan()==Scanner::ScanStatus::FAILED){
        ERROR() << "Scanning failed";
        return 1;
    }
    DEBUG() << "Scan is finished";


    DEBUG() << "End Forge::run";
    return 0;
}