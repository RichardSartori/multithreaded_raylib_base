# minimum version of cmake
cmake_minimum_required(VERSION 3.28)

# set the name of the project
# (also set variable ${PROJECT_NAME})
project(multithreaded_raylib_base)

# set C++ standard
set(CMAKE_CXX_STANDARD           20) # will add flag -std=c++20
set(CMAKE_CXX_STANDARD_REQUIRED YES) # do not decay to previous standards
set(CMAKE_CXX_EXTENSIONS        OFF) # do not use compiler extensions

# set the source files of ${PROJECT_NAME}
set(SOURCE_DIR src)
set(SOURCE_FILES
	${SOURCE_DIR}/app.hpp
	${SOURCE_DIR}/app.cpp
	${SOURCE_DIR}/configuration.hpp
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/render.hpp
	${SOURCE_DIR}/render.cpp
	${SOURCE_DIR}/update.hpp
	${SOURCE_DIR}/update.cpp
)

# executable name followed by dependencies
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# cmake build-in module to make dependencies availables
include(FetchContent)

# fetch raylib from github
FetchContent_Declare(raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib
	GIT_TAG        5.5
)

# set raylib options (must be before FetchContent_MakeAvailable(raylib))
cmake_policy(SET CMP0077 NEW)
set(CUSTOMIZE_BUILD ON CACHE BOOL "Customize raylib build")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build raylib as a static library")

# equivalent to "download raylib" + "add_subdirectory(raylib)"
# rely on raylib's CMakeLists to be properly set up
FetchContent_MakeAvailable(raylib)

# find the local thread library (pthread on Linux)
find_package(Threads REQUIRED)

# indicate that ${PROJECT_NAME} must be linked with raylib and threads
target_link_libraries(${PROJECT_NAME} PRIVATE
	raylib
	Threads::Threads
)

# indicate additional flags for debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
