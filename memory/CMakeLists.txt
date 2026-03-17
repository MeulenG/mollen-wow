cmake_minimum_required(VERSION 3.15)

project(mollen-memory-allocator)

add_library(mollen-memory-lib STATIC
	 src/mollen_alloc.cpp
)

target_compile_features(mollen-memory-lib PUBLIC cxx_std_20)
