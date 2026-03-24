cmake_minimum_required(VERSION 3.15)

add_library(mollen-wrath-lib STATIC object_mgr.cpp)

target_include_directories(mollen-wrath-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(mollen-wrath-lib PUBLIC cxx_std_20)

