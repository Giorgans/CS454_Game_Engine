//
// Created by Georgios Zervos on 22/11/23.
//

#ifndef CS454_SUPER_MARIO_GAME_PATHS_H
#define CS454_SUPER_MARIO_GAME_PATHS_H

#include "../UnitTests/ZeldaII/ZeldaII.h"

#include "UserPath.h"    // Add this file with your path as macro with the name "USER_PATH"


#define MERGE(a, b) a b

#define ICON_FILE_PATH              MERGE(USER_PATH,ZELDAII_ICON_PATH)
#define AnimationBitmaps            MERGE(USER_PATH,Zelda2_AnimationBitmaps)
#define TILESET_FILE_PATH           MERGE(USER_PATH,ZELDA_STARTING_LEVEL_TILESET_PATH)
#define BACKGROUND_CSV_FILE_PATH    MERGE(USER_PATH,ZELDA_STARTING_LEVEL_BACKGROUND_CSV_PATH)
#define TERRAIN_CSV_FILE_PATH       MERGE(USER_PATH,ZELDA_STARTING_LEVEL_TERRAIN_CSV_PATH)

#define LEVEL_STARTING_POINT_X      ZELDA_STARTING_LEVEL_STARTING_POINT_X
#define LEVEL_STARTING_POINT_Y      ZELDA_STARTING_LEVEL_STARTING_POINT_Y
#define PLAYER_STARTING_POINT_X     LINK_STARTING_POINT_X
#define PLAYER_STARTING_POINT_Y     LINK_STARTING_POINT_Y


#endif //CS454_SUPER_MARIO_GAME_PATHS_H
