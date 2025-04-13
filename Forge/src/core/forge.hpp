#pragma once
#include <print>

class Forge {
public:
    Forge() = default;
    ~Forge() = default;
    
    static Forge& init();
    
    int run(int argc, char** argv);
};