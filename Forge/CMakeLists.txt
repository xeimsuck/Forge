file(GLOB_RECURSE 
    FORGE_SOURCES
    "src/*.cpp")

add_executable(forge ${FORGE_SOURCES})

target_include_directories(forge PRIVATE "src")