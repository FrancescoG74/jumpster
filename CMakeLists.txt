cmake_minimum_required(VERSION 3.16)
project(jumpster LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} include)


set(SOURCES
	src/main.cpp
	src/Hamster.cpp
	src/Background.cpp
	src/PlatformSet.cpp
)

add_executable(jumpster ${SOURCES})
target_link_libraries(jumpster ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} SDL2_image)
