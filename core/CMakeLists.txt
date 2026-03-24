cmake_minimum_required(VERSION 3.15)

add_subdirectory(expansions)

add_library(mollen-core-lib INTERFACE)
target_link_libraries(mollen-core-lib INTERFACE mollen-wrath-lib)
