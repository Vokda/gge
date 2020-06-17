cmake_minimum_required (VERSION 3.0)
project(gge)

#  debug options
add_definitions(-DDEBUG)

# sdl2
# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH $ENV{HOME}/Projects/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# chaiscript
include_directories(${PROJECT_SOURCE_DIR}/ChaiScript/include/)

# aux_source_directory("../" SOURCE_FILES)
# source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
message(STATUS "source files: ${SOURCE_FILES}")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} dl)

# C flags
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_COMPILER g++)
