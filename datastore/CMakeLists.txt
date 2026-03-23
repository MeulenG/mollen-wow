cmake_minimum_required(VERSION 3.15)

project(mollen-datastore)

add_library(mollen-datastore-lib STATIC
	 src/cdatastore.cpp
)

target_include_directories(mollen-datastore-lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(mollen-datastore-lib PUBLIC cxx_std_20)
