cmake_minimum_required(VERSION 3.5)
project(particulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} main.cpp)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/particles)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/grid)
INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.10.1/include)
LINK_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.10.1/lib)

file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.10.1/lib/*.dylib")
#file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/*.h")

message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
