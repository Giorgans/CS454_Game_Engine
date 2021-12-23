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
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile);
void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
void BitmapBlitScaled(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
class TileLayer {
    private:
        Index map[MAX_HEIGHT][MAX_WIDTH] ;
        //GridLayer* grid = nullptr;
        Dim totalRows = 0, totalColumns = 0;
        ALLEGRO_BITMAP *tileSet = nullptr;
        Rect viewWin{0,0,DISPLAY_W,DISPLAY_H};
        ALLEGRO_BITMAP *dpyBuffer = nullptr;
        bool dpyChanged = true;
        Dim dpyX = 0, dpyY = 0;
        void Allocate(void) {
            this->dpyBuffer = al_create_bitmap((MAX_WIDTH + 2) * TILE_WIDTH, (MAX_HEIGHT + 2) * TILE_HEIGHT);
        }
    public:
        void SetTile (Dim row,Dim col, Index index) { this->map[row][col] = index; }
        Index GetTile (Dim row,Dim col) { return this->map[row][col]; }
        const Point Pick (Dim x, Dim y) const {
            return { DIV_TILE_WIDTH(x + viewWin.x),
                 DIV_TILE_HEIGHT(y + viewWin.y) };
        }
        const Rect& GetViewWindow (void) const { return viewWin; }
        void SetViewWindow (const Rect& r) { viewWin = r; dpyChanged = true; }
        void Display (ALLEGRO_BITMAP *dest, const Rect& displayArea);
        ALLEGRO_BITMAP *GetBitmap (void) const { return dpyBuffer; }
        int GetPixelWidth (void) const { return viewWin.w; }
        int GetPixelHeight (void) const { return viewWin.h; }
        unsigned GetTileWidth (void) const { return DIV_TILE_WIDTH(viewWin.w); }
        unsigned GetTileHeight (void) const { return DIV_TILE_HEIGHT(viewWin.h); }
        void Scroll (float dx, float dy);
        bool CanScrollHoriz (float dx) const;
        bool CanScrollVert (float dy) const;
        auto ToString (void) const -> const std::string;
        bool FromString (const std::string&);
        void Save (const std::string& path) ;
        bool Load (const std::string& path);
        FILE* WriteText (FILE* fp) const    { fprintf(fp, "%s", ToString().c_str()); return fp; }
        bool ReadText (std::string path);
        TileLayer (Dim rows, Dim cols, ALLEGRO_BITMAP *tileSet,std::string path);
        ~TileLayer ();
};

Dim TileX (byte index);
Dim TileY (byte index);
void Rendering(void);


#endif //CS454_SUPER_MARIO_GAME_RENDERING_H
