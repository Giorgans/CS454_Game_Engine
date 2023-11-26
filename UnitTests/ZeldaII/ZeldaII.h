//
// Created by Georgios Zervos on 24/11/23.
//

#ifndef CS454_GAME_ENGINE_ZELDAII_H
#define CS454_GAME_ENGINE_ZELDAII_H
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#define FRAME_DURATION 1000/60 // 60 FPS

#define KEY_COLOR al_map_rgb(0,0,1)
#define EMPTY_TILE 40

/***************************************
 *  Macros of paths                   *
 **************************************/

#define Zelda2_AnimationBitmaps "/UnitTests/ZeldaII/Media/AnimationFilmBitmaps/Link"
#define ZELDAII_ICON_PATH "/UnitTests/ZeldaII/Media/icon.jpg"
#define ZELDA_II_TITLE_SCREEN_MUSIC "/UnitTests/ZeldaII/Media/Sound/01. Title Screen - Prologue.wav"
#define ZELDA_II_PALACE_INTRO_MUSIC "/UnitTests/ZeldaII/Media/Sound/12. Palace Theme 1.wav"
#define ZELDA_II_PALACE_NOINTRO_MUSIC "UnitTests/ZeldaII/Media/Sound/13. Palace Theme 1 (No Intro).wav"
#define ZELDA_II_ATTACK_SOUND "UnitTests/ZeldaII/Media/Sound/attack.wav"

/***************************************
 *  Choosing Starting level macros    *
 **************************************/

#define ZELDA_STARTING_LEVEL_TILESET_PATH           PARAPA_PALACE_LEVEL_TILESET_PATH
#define ZELDA_STARTING_LEVEL_BACKGROUND_CSV_PATH    PARAPA_PALACE_LEVEL_BACKGROUND_CSV_PATH
#define ZELDA_STARTING_LEVEL_TERRAIN_CSV_PATH       PARAPA_PALACE_LEVEL_TERRAIN_CSV_PATH

/***************************************
 *  Starting Position macros for render *
 **************************************/

#define ZELDA_STARTING_LEVEL_STARTING_POINT_X       PARAPA_PALACE_LEVEL_STARTING_POINT_X
#define ZELDA_STARTING_LEVEL_STARTING_POINT_Y       PARAPA_PALACE_LEVEL_STARTING_POINT_Y

#define LINK_STARTING_POINT_X                       PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_X
#define LINK_STARTING_POINT_Y                       PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_Y

/***************************************
 *  Player's Moveset macros for lookup *
 **************************************/

#define WalkingRight "link.right.png"
#define WalkingLeft "link.left.png"
#define WalkingUp "" // For top-down 2D games
#define WalkingDown ""  // For top-down 2D games
#define DownLeft "link.DownAttack.left.png"
#define DownRight "link.DownAttack.right.png"
#define AttackLeft "link.attack.left.png"
#define AttackRight "link.attack.right.png"

/***************************************
 *  Parapa Palace Level Macros         *
***************************************/

#define PARAPA_PALACE_LEVEL_TILESET_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/tileset.png"
#define PARAPA_PALACE_LEVEL_BACKGROUND_CSV_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/parapa_palace_background.csv"
#define PARAPA_PALACE_LEVEL_TERRAIN_CSV_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/parapa_palace_terrain.csv"
#define PARAPA_PALACE_LEVEL_STARTING_POINT_X 64 << 4
#define PARAPA_PALACE_LEVEL_STARTING_POINT_Y 3 << 4
#define PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_X  66 << 4
#define PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_Y  12 << 4

/***************************************
 *  Main Loop Functions               *
 **************************************/

void ZeldaII_Rendering();
void ZeldaII_Animations();
void ZeldaII_Input();
void ZeldaII_Sound();

/***************************************
 *  Animation Functions               *
 **************************************/

void Link_Animations();

/***************************************
 *  Creating Sprites Functions        *
 **************************************/

void createLink();


/***************************************
 *  Initialization Functions          *
 **************************************/

void InitializeBitmaps();
void InitializeFilms();
void InitializeAnimators();
void InitializeInputs();



#endif //CS454_GAME_ENGINE_ZELDAII_H
