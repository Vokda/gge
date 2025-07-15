cmake_minimum_required (VERSION 3.8)
project(gge)

include(CMakePrintHelpers)

#set(CMAKE_BUILD_TYPE Debug)

#  debug options
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra -Werror -Wno-error=unused-function -Wno-error=unused-parameter")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
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

find_package(Log4cpp REQUIRED)
include_directories(${LOG4CPP_INCLUDE_DIR})

set(LIBRARIES ${LOG4CPP_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_SUPPORT_LIBRARIES} ${GUILE_LIBRARY})

# aux_source_directory("../" SOURCE_FILES)
# source files
file(GLOB_RECURSE SOURCE_FILES "src/*.c*")
#string(REGEX REPLACE ".cpp" ".cpp\n" OUT ${SOURCE_FILES} )
#message(STATUS "Files to be compiled\n" ${OUT})

#execute_process(COMMAND perl build_tools/generate_gge_api_defaults.pl WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#execute_process(COMMAND perl build_tools/generate_get_gge_modules.pl WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} GL)
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_SUPPORT_LIBRARIES} ${GUILE_LIBRARY})
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} dl , ${GUILE_LIBRARY})

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++17" )
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_COMPILER clang++)
