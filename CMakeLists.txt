
cmake_minimum_required(VERSION 3.20)
project(CS454_Super_Mario_Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(CS454_Super_Mario_Game main.cpp Engine/timing.cpp Engine/timing.h app.cpp app.h)

INCLUDE_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.7.0/include )
LINK_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.7.0/lib )

file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.7.0/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(CS454_Super_Mario_Game  ${LIBRARIES})



