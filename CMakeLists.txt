cmake_minimum_required(VERSION 3.22)
project(mollen-wow)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

option(WRATH "Enable Wrath 3.3.5a expansion" ON)

add_subdirectory(memory)
add_subdirectory(datastore)
add_subdirectory(core)
add_subdirectory(tests)

add_executable(mollen-wow main.cpp)
target_compile_features(mollen-wow PRIVATE cxx_std_20)

target_link_libraries(mollen-wow PRIVATE
    mollen-memory-lib
    mollen-datastore-lib
    mollen-core-lib
)
