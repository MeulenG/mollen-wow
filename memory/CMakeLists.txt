cmake_minimum_required(VERSION 3.15)

project(mollen-memory-allocator)

add_library(mollen-memory-lib STATIC
	 src/mollen_alloc.cpp
	 ${CMAKE_SOURCE_DIR}/utils/hooks/hook.cpp
)

target_include_directories(mollen-memory-lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/utils
)

target_compile_features(mollen-memory-lib PUBLIC cxx_std_20)
