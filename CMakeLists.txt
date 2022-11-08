
cmake_minimum_required(VERSION 3.20)
project(CS454_Super_Mario_Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
add_executable(CS454_Super_Mario_Game Engine/Src/timing.cpp Engine/Include/timing.h app.cpp app.h Engine/Src/terrain.cpp Engine/Include/terrain.h game.cpp Engine/Src/rendering.cpp Engine/Include/rendering.h Engine/Include/input.h Engine/Src/input.cpp Engine/Include/animation.h Engine/Src/animation.cpp Engine/Include/sprite.h Engine/Src/sprite.cpp Engine/Include/physics.h Engine/Src/physics.cpp)
INCLUDE_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.7.0/include )
LINK_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.7.0/lib )
file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.7.0/lib/*.dylib")
MESSAGE(LIBRARIES = ${LIBRARIES})

TARGET_LINK_LIBRARIES(CS454_Super_Mario_Game ${LIBRARIES})
set(MACOSX_BUNDLE_BUNDLE_NAME "CS454_Super_Mario_Game")
set(MACOSX_BUNDLE_BUNDLE_VERSION "Version 0.1")
set(MACOSX_BUNDLE_COPYRIGHT "Copyright Georgios Zervos")

set(icon_name "marioapp.icns")
set(icon_location /Users/george/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/${icon_name})
if(EXISTS "${icon_location}")
    set_target_properties(CS454_Super_Mario_Game PROPERTIES MACOSX_BUNDLE_ICON_FILE ${icon_name})
    set_target_properties(CS454_Super_Mario_Game PROPERTIES MACOSX_BUNDLE_ICON_FILE ${icon_location})
    file(COPY ${icon_location} DESTINATION "/Users/george/CLionProjects/CS454_Super_Mario_Game/cmake-build-debug/CS454_Super_Mario_Game.app/Contents/Resources/")
    file(INSTALL ${icon_location} DESTINATION "/Users/george/CLionProjects/CS454_Super_Mario_Game/cmake-build-debug/CS454_Super_Mario_Game.app/Contents/Resources")
endif()

set_target_properties(CS454_Super_Mario_Game PROPERTIES MACOSX_BUNDLE_ICON_FILE marioapp.icns MACOSX_BUNDLE TRUE)
install(TARGETS CS454_Super_Mario_Game DESTINATION GAME_TEST)
