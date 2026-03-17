cmake_minimum_required(VERSION 3.22)
project(mollen-wow)


add_subdirectory(memory)

add_executable(mollen-wow main.cpp)

target_include_directories(mollen-memory-lib 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/memory/include
)

target_link_libraries(mollen-wow PRIVATE mollen-memory-lib)
