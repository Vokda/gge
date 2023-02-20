cmake_minimum_required (VERSION 3.0)
project(gge)

include(CMakePrintHelpers)

#set(CMAKE_BUILD_TYPE Debug)

#  debug options
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	add_definitions(-DDEBUG)
	set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0 -g -Wall")
endif()

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH cmake/)

# sdl2
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_SUPPORT_LIBRARIES REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}) 

find_package(Guile REQUIRED)
include_directories(${GUILE_INCLUDE_DIR})

# aux_source_directory("../" SOURCE_FILES)
# source files
file(GLOB_RECURSE SOURCE_FILES "src/*.c*")
message(STATUS ${SOURCE_FILES} )

#execute_process(COMMAND perl build_tools/generate_gge_api_defaults.pl WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#execute_process(COMMAND perl build_tools/generate_get_gge_modules.pl WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_SUPPORT_LIBRARIES} ${GUILE_LIBRARY})
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} dl , ${GUILE_LIBRARY})

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++17" )
set(CMAKE_CXX_COMPILER clang++)
