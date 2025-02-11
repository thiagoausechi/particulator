cmake_minimum_required(VERSION 3.5)
project(particulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCE_FILES main.cpp)

add_executable(particulator main.cpp)

INCLUDE_DIRECTORIES(  /opt/homebrew/Cellar/allegro/5.2.10.1/include )
LINK_DIRECTORIES(  /opt/homebrew/Cellar/allegro/5.2.10.1/lib )

file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.10.1/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(particulator  ${LIBRARIES})
