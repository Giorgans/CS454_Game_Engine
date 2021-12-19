
cmake_minimum_required(VERSION 3.20)
project(CS454_Super_Mario_Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
add_executable(CS454_Super_Mario_Game Engine/Src/timing.cpp Engine/Include/timing.h app.cpp app.h Engine/Src/terrain.cpp Engine/Include/terrain.h game.cpp Engine/Src/rendering.cpp Engine/Include/rendering.h Engine/Include/input.h Engine/Src/input.cpp)

INCLUDE_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.7.0/include  /usr/local/Cellar/libpng/1.6.37/include )
LINK_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.7.0/lib  /usr/local/Cellar/libpng/1.6.37/lib)
file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.7.0/lib/*.dylib" "/usr/local/Cellar/libpng/1.6.37/lib/*.dylib")
MESSAGE(LIBRARIES = ${LIBRARIES})

TARGET_LINK_LIBRARIES(CS454_Super_Mario_Game ${LIBRARIES})



