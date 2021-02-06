# CMake version
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Builds/CMake")

# Declare project
project(AlgorithmPlayground)

# Set enable output of compile commands during generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build type - Release by default
message("CMake build type: " ${CMAKE_BUILD_TYPE})
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
endif()

# Compile options
include(Builds/CMake/CompileOptions.cmake)

# Overrides
set(CMAKE_MACOSX_RPATH ON)

# Set resources
set(BAEKJOON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Baekjoon)
set(ALGOSPOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Algospot)

file(GLOB_RECURSE BAEKJOON_PROBLEMS
	"${BAEKJOON_SOURCE_DIR}/*.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/baekjoon)

foreach(PROBLEM ${BAEKJOON_PROBLEMS})
	get_filename_component(FILE_NAME ${PROBLEM} NAME_WE)
	add_executable(Baekjoon${FILE_NAME} ${PROBLEM})
endforeach(PROBLEM)

file(GLOB_RECURSE ALGOSPOT_PROBLEMS
	"${ALGOSPOT_SOURCE_DIR}/*.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/algospot)

foreach(PROBLEM ${ALGOSPOT_PROBLEMS})
	get_filename_component(FILE_NAME ${PROBLEM} NAME_WE)
	add_executable(Algospot${FILE_NAME} ${PROBLEM})
endforeach(PROBLEM)