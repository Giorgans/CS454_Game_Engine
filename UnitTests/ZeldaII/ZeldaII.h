
#ifndef CS454_GAME_ENGINE_ZELDAII_H
#define CS454_GAME_ENGINE_ZELDAII_H
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "src/Enemy.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <random>

#define FRAME_DURATION 1000/14


#include <map>
extern std::map<std::string,bool> inputs;
extern std::vector<Enemy> enemyHealthList;

struct SpriteVisibilityInfo {
    bool isVisible;
    int distanceFromLink; // Signed distance from Link
};


#define KEY_COLOR al_map_rgb(0,0,1)
#define EMPTY_TILE 40
#define KEY_TILE 72
#define ELEVATOR_TILE 18
#define CANDLE_TILE 73
#define BRIDGE_TILE 68
#define FAIRY_TILE 89
#define DOOR_TILE 35

#define WOSU_ENEMY_TILE 56
#define BOT_TILE 92
#define STALFOS_TILE 94

#define ATTACK_RANGE 40
#define PUSH_BACK 8

/***************************************
 *  Macros of paths                   *
 **************************************/

#define Zelda2_AnimationBitmaps "/UnitTests/ZeldaII/Media/AnimationFilmBitmaps"
#define ZELDAII_ICON_PATH "/UnitTests/ZeldaII/Media/icon.jpg"
#define ZELDA_II_TITLE_SCREEN_MUSIC "/UnitTests/ZeldaII/Media/Sound/01. Title Screen - Prologue.wav"
#define ZELDA_II_PALACE_INTRO_MUSIC "/UnitTests/ZeldaII/Media/Sound/12. Palace Theme 1.wav"
#define ZELDA_II_PALACE_NOINTRO_MUSIC "UnitTests/ZeldaII/Media/Sound/13. Palace Theme 1 (No Intro).wav"
#define ZELDA_II_ATTACK_SOUND "/UnitTests/ZeldaII/Media/Sound/attack.wav"
#define ZELDA_II_PALACE_LEVEL_MUSIC "/UnitTests/ZeldaII/Media/Sound/12. Palace Theme 1.wav"


/***************************************
 *  Choosing Starting level macros    *
 **************************************/

#define ZELDA_STARTING_LEVEL_TILESET_PATH           PARAPA_PALACE_LEVEL_TILESET_PATH
#define ZELDA_STARTING_LEVEL_BACKGROUND_CSV_PATH    PARAPA_PALACE_LEVEL_BACKGROUND_CSV_PATH
#define ZELDA_STARTING_LEVEL_TERRAIN_CSV_PATH       PARAPA_PALACE_LEVEL_TERRAIN_CSV_PATH
#define ZELDA_STARTING_LEVEL_OBJECTS_CSV_PATH      PARAPA_PALACE_LEVEL_OBJECTS_AND_ENEMIES_CSV_PATH
/***************************************
 *  Starting Position macros for render *
 **************************************/

#define ZELDA_STARTING_LEVEL_STARTING_POINT_X       PARAPA_PALACE_LEVEL_STARTING_POINT_X
#define ZELDA_STARTING_LEVEL_STARTING_POINT_Y       PARAPA_PALACE_LEVEL_STARTING_POINT_Y

#define LINK_STARTING_POINT_X                       PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_X
#define LINK_STARTING_POINT_Y                       PARAPA_PALACE_LEVEL_LINK_STARTING_POINT_Y

/***************************************
 *  File macros for lookup           *
 **************************************/
#define PauseScreen "pause_screen.png"
#define TitleScreen "titlescreen.png"
/* Link's Animations */
#define WalkingRight "link.right.png"
#define WalkingLeft "link.left.png"
#define DownLeft "link.DownAttack.left.png"
#define DownRight "link.DownAttack.right.png"
#define AttackLeft "link.attack.left.png"
#define AttackRight "link.attack.right.png"
#define JumpRight "link.jump.right.png"
#define JumpLeft "link.jump.left.png"
#define JumpAttackUpRight "link.jump.attack.up.right.png"
#define JumpAttackUpLeft "link.jump.attack.up.left.png"
#define JumpAttackDownRight "link.jump.attack.down.right.png"
#define JumpAttackDownLeft "link.jump.attack.down.left.png"

/* Enemies Animations */
#define Bot "bot.png"
#define Bubble "bubble.png"
#define WosuLeft "wosu.left.png"
#define WosuRight "wosu.right.png"
#define StalfosWalkingLeft "stalfos.left.png"
#define StalfosWalkingRight "stalfos.right.png"
#define StalfosAttackLeft "stalfos.attack.left.png"
#define StalfosAttackRight "stalfos.attack.right.png"
#define StalfosJumpLeft "stalfos.jump.left.png"
#define StalfosJumpRight "stalfos.jump.right.png"

/* Objects  */
#define Key "key.png"
#define Candle "candle.png"
#define Door "door.png"
#define Elevator "elevator.png"
#define Fairy "fairy.png"
#define FallingBridge "falling.bridge.png"

/***************************************
 *  Parapa Palace Level Macros         *
***************************************/

#define PARAPA_PALACE_LEVEL_TILESET_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/tileset.png"
#define PARAPA_PALACE_LEVEL_BACKGROUND_CSV_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/parapa_palace_background.csv"
#define PARAPA_PALACE_LEVEL_TERRAIN_CSV_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/parapa_palace_terrain.csv"
#define PARAPA_PALACE_LEVEL_OBJECTS_AND_ENEMIES_CSV_PATH "/UnitTests/ZeldaII/Media/Levels/ParapaPalace/sprites_Sprites.csv"
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
void ZeldaII_Physics();

/***************************************
 *  Rendering Functions               *
 **************************************/

void tittle_screen_rendering();
void parapa_palace_level_rendering();

/***************************************
 *  Animation Functions               *
 **************************************/


/***************************************
 *  Creating Sprites Functions        *
 **************************************/

void createPauseScreen();
void createTittleScreen();
void createLink();
void createEnemiesAndObjects();

/***************************************
 *  Input Functions                    *
 **************************************/

void TitleScreenInputs();
void MainGameInputs();

/***************************************
 *  Sound Functions                   *
 **************************************/

void PlayAttackSound();
void PlayTitleScreenSound();
void PlayLevelSound();
void LoadSounds();

/***************************************
 *  Initialization Functions          *
 **************************************/

void InitializeBitmaps();
void InitializeFilms();
void InitializeAnimations();
void InitializeInputs();
void InitializeSprites();
void InitializeSounds();
void InitializeRendering();


/***************************************
 *  Useful Functions                  *
 **************************************/


#endif //CS454_GAME_ENGINE_ZELDAII_H
