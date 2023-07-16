//
// Created by Georgios Zervos on 8/12/21.
//

#ifndef CS454_SUPER_MARIO_GAME_RENDERING_H
#define CS454_SUPER_MARIO_GAME_RENDERING_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "sprite.h"
/** Definitions for tiles */
// PATHS
#define TILESET_FILE_PATH "/Users/george/CLionProjects/CS454_ZeldaII/UnitTests/ZeldaII/Media/Zelda-II-Parapa-Palace-Tileset.png"
#define BACKGROUND_CSV_FILE_PATH "/Users/george/CLionProjects/CS454_ZeldaII/UnitTests/ZeldaII/Media/zelda2map_background.csv"
#define TERRAIN_CSV_FILE_PATH "/Users/george/CLionProjects/CS454_ZeldaII/UnitTests/ZeldaII/Media/zelda2map_terrain.csv"
#define ICON_FILE_PATH "/Users/george/CLionProjects/CS454_ZeldaII/UnitTests/ZeldaII/Media/icon.jpg"

void Rendering();

#endif //CS454_SUPER_MARIO_GAME_RENDERING_H
