cmake_minimum_required (VERSION 3.0)
project(gge)

#  debug options
add_definitions(-DDEBUG)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH cmake/)

# sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_SUPPORT_LIBRARIES REQUIRED)

message(STATUS "sdl2 include dir ${SDL2_INCLUDE_DIR}")

# chaiscript
include_directories(${PROJECT_SOURCE_DIR}/ChaiScript/include/)

# aux_source_directory("../" SOURCE_FILES)
# source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
message(STATUS "source files: ${SOURCE_FILES}")

#execute_process(COMMAND perl build_tools/generate_gge_api_defaults.pl WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#execute_process(COMMAND perl build_tools/generate_get_gge_modules.pl WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} dl ${SDL2_SUPPORT_LIBRARIES})

# C flags
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_COMPILER clang++)
