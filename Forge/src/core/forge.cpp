#include <core/forge.hpp>
#include <logger/logger.hpp>

Forge& Forge::init(){
    static Forge instance;
    return instance;
}

int Forge::run(int argc, char** argv){
    DEBUG() << "Run Forge::run";

    if(argc!=1) {
        FATAL() << "[FORGE] - Usage: forge";
        return 1;
    }

    DEBUG() << "End Forge::run";
    return 0;
}