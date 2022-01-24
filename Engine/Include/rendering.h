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

/** Definitions for tiles */
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
#define TILESET_FILE_PATH "/Users/iasonasntagiannes/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/mariofulltileset.png"
#define BACKGROUND_CSV_FILE_PATH "/Users/iasonasntagiannes/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/Levels/1-1/1-1_Background.csv"
#define TERRAIN_CSV_FILE_PATH "/Users/iasonasntagiannes/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/Levels/1-1/1-1_Terrain.csv"
#define ICON_FILE_PATH "/Users/iasonasntagiannes/CLionProjects/CS454_Super_Mario_Game/UnitTests/SuperMarioBros/Media/icon.png"
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
class TileLayer;
class GridLayer;


class TileLayer {
    private:
        Index map[MAX_HEIGHT][MAX_WIDTH] ;
        GridLayer* grid = nullptr;
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


/** Definitions for Grid */
#define GRID_ELEMENT_WIDTH 4
#define GRID_ELEMENT_HEIGHT 4
#if TILE_WIDTH % GRID_ELEMENT_WIDTH != 0
#error "TILE_WIDTH % GRID_ELEMENT_WIDTH must be zero!"
#endif
#if TILE_HEIGHT % GRID_ELEMENT_HEIGHT != 0
#error "TILE_HEIGHT % GRID_ELEMENT_HEIGHT must be zero!"
#endif
#define GRID_BLOCK_COLUMNS (TILE_WIDTH / GRID_ELEMENT_WIDTH)
#define GRID_BLOCK_ROWS (TILE_HEIGHT / GRID_ELEMENT_HEIGHT)
#define GRID_ELEMENTS_PER_TILE (GRID_BLOCK_ROWS * GRID_BLOCK_COLUMNS)
#define GRID_MAX_HEIGHT (MAX_HEIGHT * GRID_BLOCK_ROWS)
#define GRID_MAX_WIDTH (MAX_WIDTH * GRID_BLOCK_COLUMNS)
using GridIndex = byte;
typedef GridIndex GridMap[GRID_MAX_WIDTH][GRID_MAX_HEIGHT];

#define GRID_THIN_AIR_MASK 0x0000 // element is ignored
#define  GRID_LEFT_SOLID_MASK 0x0001 // bit 0
#define  GRID_RIGHT_SOLID_MASK 0x0002 // bit 1
#define GRID_TOP_SOLID_MASK  0x0004 // bit 2
#define GRID_BOTTOM_SOLID_MASK 0x0008 // bit 3
#define GRID_GROUND_MASK 0x0010 // bit 4, keep objects top / bottom (gravity)
#define GRID_FLOATING_MASK 0x0020  // bit 5, keep objects anywhere inside (gravity)
#define GRID_EMPTY_TILE GRID_THIN_AIR_MASK
#define GRID_SOLID_TILE (GRID_LEFT_SOLID_MASK | GRID_RIGHT_SOLID_MASK | GRID_TOP_SOLID_MASK | GRID_BOTTOM_SOLID_MASK)
#define MAX_PIXEL_WIDTH MUL_TILE_WIDTH(MAX_WIDTH)
#define MAX_PIXEL_HEIGHT MUL_TILE_HEIGHT(MAX_HEIGHT)
#define DIV_GRID_ELEMENT_WIDTH(i) ((i)>>2)
#define DIV_GRID_ELEMENT_HEIGHT(i) ((i)>>2)
#define MUL_GRID_ELEMENT_WIDTH(i) ((i)<<2)
#define MUL_GRID_ELEMENT_HEIGHT(i) ((i)<<2)
static Index tilesFlags[239] = {};
const Index solidTiles[35] =  {0,1,2,3,7,8,16,23,24,32,64,65,66,67,68,69,71,72,87,88,101,102,103,117,118,119,160,161,162,163,164,176,177,178,179};
void initialiseTileFlags();

#define GRID_BLOCK_SIZEOF \
(GRID_ELEMENTS_PER_TILE * sizeof(GridIndex))

#define SetGridTileBlockEmpty(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_EMPTY_TILE)

#define SetGridTileBlockSolid(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_SOLID_TILE)

GridIndex* GetGridTileBlock (Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid) { return grid + (rowTile * tileCols + colTile) * GRID_BLOCK_SIZEOF;
}



void SetGridTileBlock (Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid, GridIndex flags) {
    memset(
            GetGridTileBlock(colTile, rowTile, tileCols, grid), flags,
            GRID_BLOCK_SIZEOF
    );
}

class GridLayer {
    private:
        GridIndex * grid = nullptr;
        unsigned total = 0;
        Dim totalRows = 0, totalColumns = 0;
        void Allocate (void) {
            grid = new GridIndex [total = totalRows * totalColumns];
            std::memset(grid, GRID_EMPTY_TILE, total);
        }
        void SetGridTile ( Dim col, Dim row, GridIndex index) { *(grid + (row * totalColumns) + col) = index; }
        GridIndex GetGridTile (Dim col, Dim row) { return *(grid + (row * totalColumns) + col); }
        void SetSolidGridTile (Dim col, Dim row) { SetGridTile( col, row, GRID_SOLID_TILE); }
        void SetEmptyGridTile ( Dim col, Dim row) { SetGridTile( col, row, GRID_EMPTY_TILE); }
        void SetGridTileFlags (Dim col, Dim row, GridIndex flags) { SetGridTile( col, row, flags); }
        void SetGridTileTopSolidOnly (Dim col, Dim row) { SetGridTileFlags( row, col, GRID_TOP_SOLID_MASK); }
        bool CanPassGridTile (Dim col, Dim row, Index flags) { return GetGridTile(row, col) & (flags != 0); }
        // TODO: adapt as needed and insert all rest motion control functions
        // inside the private section
        void     FilterGridMotionDown (const Rect& r, int* dy) ;
        void     FilterGridMotionUp (const Rect& r, int* dy) ;
        void     FilterGridMotionRight (const Rect& r, int* dx) ;
        void     FilterGridMotionLeft (const Rect& r, int* dx) ;

    public:
        void FilterGridMotion (const Rect& r, int* dx, int* dy) ;
        bool IsOnSolidGround (const Rect& r)  { // will need later for gravity
            int dy = 1; // down 1 pixel
            FilterGridMotionDown(r, &dy);
            return dy == 0; // if true IS attached to solid ground
        }
        GridIndex*& GetBuffer(void) { return grid; }
        //const GridIndex*& GetBuffer(void) const { return  grid ; }
        GridLayer (unsigned rows, unsigned cols);
};

bool isTileIndexAssumedSolid(Index index);



#endif //CS454_SUPER_MARIO_GAME_RENDERING_H
