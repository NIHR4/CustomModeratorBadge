cmake_minimum_required(VERSION 3.18.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ProfileBadges VERSION 1.0.0)

#Packages
find_package(minhook CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)


file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(ProfileBadges SHARED ${SOURCE_FILES})

#Git submodules
add_subdirectory(deps/matdash)
add_subdirectory(deps/cocos-headers)

#Linking
target_link_libraries(ProfileBadges PRIVATE 
    minhook::minhook
    spdlog::spdlog
    mat-dash
    cocos2d
)