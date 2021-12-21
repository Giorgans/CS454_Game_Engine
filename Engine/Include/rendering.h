//
// Created by Georgios Zervos on 8/12/21.
//

#ifndef CS454_SUPER_MARIO_GAME_RENDERING_H
#define CS454_SUPER_MARIO_GAME_RENDERING_H
#include <allegro5/allegro.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#define KEY_COLOR al_map_rgb(148,148,255)
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
#define TILESET_FILE_PATH "/Users/george/Desktop/Μαθήματα/HY-454 Video Game/Project2021/CS454-Super-Mario-Game/UnitTests/SuperMarioBros/Media/mariofulltileset.png"
#define BACKGROUND_CSV_FILE_PATH "/Users/george/Desktop/Μαθήματα/HY-454 Video Game/Project2021/CS454-Super-Mario-Game/UnitTests/SuperMarioBros/Media/Levels/1-1/1-1_Background.csv"
#define TERRAIN_CSV_FILE_PATH "/Users/george/Desktop/Μαθήματα/HY-454 Video Game/Project2021/CS454-Super-Mario-Game/UnitTests/SuperMarioBros/Media/Levels/1-1/1-1_Terrain.csv"
#define ICON_FILE_PATH "/Users/george/Desktop/Μαθήματα/HY-454 Video Game/Project2021/CS454-Super-Mario-Game/UnitTests/SuperMarioBros/Media/icon.png"
//
typedef unsigned short Dim;
struct Rect { int x, y, w, h; };
struct Point { int x, y; };
enum BitDepth { bits8 = 1, bits16 = 2, bits24 = 3, bits32 = 4 };
typedef unsigned char byte;
typedef unsigned short Index; // [MSB X][LSB Y]
typedef Index TileMap[MAX_WIDTH][MAX_HEIGHT];
static TileMap map; // example of a global static map
bool Open (Dim rw, Dim rh, BitDepth depth);
void Close (void);
Dim GetResWidth (void);
Dim GetResHeight (void);
BitDepth GetDepth (void);
byte MakeIndex (byte row, byte col );
Index MakeIndex2 (byte row, byte col);
byte GetCol (byte index);
byte GetRow (byte index);
Dim TileX (byte index);
Dim TileY (byte index);
Dim TileX2 (byte index);
Dim TileY2 (byte index);
Dim TileX3 (Index index);
Dim TileY3 (Index index);
void SetTile (TileMap* m, Dim col, Dim row, Index index);
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile);
Index GetTile (const TileMap* m, Dim col, Dim row) ;
void WriteBinMap (const TileMap* m, FILE* fp);
bool ReadBinMap (TileMap* m, FILE* fp);
void WriteTextMap (const TileMap*, FILE* fp);

int GetMapPixelWidth (void);
int GetMapPixelHeight (void);
void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);

bool ReadTextMap (TileMap *m, std::string path);
void TileTerrainDisplay (TileMap* map, ALLEGRO_BITMAP *dest, const Rect& viewWin, const Rect& displayArea);

void Rendering(void);

#endif //CS454_SUPER_MARIO_GAME_RENDERING_H
