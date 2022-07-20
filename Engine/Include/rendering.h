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

/** Definitions for tiles */
#define KEY_COLOR al_map_rgb(148,148,255)
#define TRANSPARENT al_map_rgba(0,0,0,0)
#define FPS 60
#define DISPLAY_W 640
#define DISPLAY_H 480
#define TILESET_WIDTH 16
#define TILESET_HEIGHT 16
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define EMPTY_TILE 40
//Max storage of tile map
#define MAX_WIDTH 211
#define MAX_HEIGHT 30
//Moving tiles for 16x16 tileset bitmap
#define ROW_MASK 0x0F
#define COL_MASK 0xF0
#define COL_SHIFT 4
#define TILEX_SHIFT 8
#define TILEX_MASK 0xFF00
#define TILEY_MASK 0x00FF
// Moving tiles
#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i)((i)&15)
// PATHS
#define TILESET_FILE_PATH "/Users/george/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/mariofulltileset.png"
#define BACKGROUND_CSV_FILE_PATH "/Users/george/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/Levels/1-1/1-1_Background.csv"
#define TERRAIN_CSV_FILE_PATH "/Users/george/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/Levels/1-1/1-1_Terrain.csv"
#define ICON_FILE_PATH "/Users/george/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/unnamed.png"
//


typedef unsigned short Dim;
struct Rect { int x, y, w, h; };
struct Point { int x, y; };
typedef unsigned char byte;
typedef unsigned short Index;
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile);
void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
void BitmapBlitScaled(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
Dim TileX (byte index);
Dim TileY (byte index);
void Rendering(void);

#endif //CS454_SUPER_MARIO_GAME_RENDERING_H
