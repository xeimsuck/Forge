#include <core/forge.hpp>

int main(int argc, char** argv){
    auto& instance = Forge::init();
    return instance.run(argc, argv);
}