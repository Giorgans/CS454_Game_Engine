//
// Created by Georgios Zervos on 24/11/23.
//

#ifndef CS454_GAME_ENGINE_ZELDAII_H
#define CS454_GAME_ENGINE_ZELDAII_H




#define KEY_COLOR al_map_rgb(0,0,1)
#define EMPTY_TILE 40


#define Zelda2_AnimationBitmaps "/UnitTests/ZeldaII/Media/AnimationFilmBitmaps/Link"
#define ZELDAII_ICON_PATH "/UnitTests/ZeldaII/Media/icon.jpg"

#define PARAPA_PALACE_LEVEL_TILESET_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/tileset.png"
#define PARAPA_PALACE_LEVEL_BACKGROUND_CSV_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/parapa_palace_background.csv"
#define PARAPA_PALACE_LEVEL_TERRAIN_CSV_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/parapa_palace_terrain.csv"
#define PARAPA_PALACE_LEVEL_STARTING_POINT_X 64 << 4
#define PARAPA_PALACE_LEVEL_STARTING_POINT_Y 3 << 4
#define PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_X  66 << 4
#define PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_Y  12 << 4


#define ZELDA_STARTING_LEVEL_TILESET_PATH           PARAPA_PALACE_LEVEL_TILESET_PATH
#define ZELDA_STARTING_LEVEL_BACKGROUND_CSV_PATH    PARAPA_PALACE_LEVEL_BACKGROUND_CSV_PATH
#define ZELDA_STARTING_LEVEL_TERRAIN_CSV_PATH       PARAPA_PALACE_LEVEL_TERRAIN_CSV_PATH
#define ZELDA_STARTING_LEVEL_STARTING_POINT_X       PARAPA_PALACE_LEVEL_STARTING_POINT_X
#define ZELDA_STARTING_LEVEL_STARTING_POINT_Y       PARAPA_PALACE_LEVEL_STARTING_POINT_Y

#define LINK_STARTING_POINT_X                       PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_X
#define LINK_STARTING_POINT_Y                       PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_Y

#define WalkingRight "link.right.png"
#define WalkingLeft "link.left.png"
#define WalkingUp "" // For top-down 2D games
#define WalkingDown ""  // For top-down 2D games
#define DownLeft "link.DownAttack.left.png"
#define DownRight "link.DownAttack.right.png"
#define AttackLeft "link.attack.left.png"
#define AttackRight "link.attack.right.png"

void createLink();


#endif //CS454_GAME_ENGINE_ZELDAII_H
