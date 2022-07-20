//
// Created by Georgios Zervos on 18/11/21.
//

#ifndef CS454_SUPER_MARIO_GAME_TERRAIN_H
#define CS454_SUPER_MARIO_GAME_TERRAIN_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "rendering.h"

class TileLayer;
class GridLayer;

class TileLayer {
private:
    Index map[MAX_HEIGHT][MAX_WIDTH] ;
    GridLayer *grid;
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
    ALLEGRO_BITMAP *GetBuffer(){return this->dpyBuffer;}
    GridLayer *GetGrid(){return this->grid;}
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
    Dim getCols(){return totalColumns;}
    bool CanScrollHoriz (float dx){
        //Checking if the level has ended
        if(GetViewWindow().x + dx == (getCols()*TILE_WIDTH - 20*TILE_WIDTH)) return true;
        else return false;
    }
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

#define GRID_BLOCK_SIZEOF \
(GRID_ELEMENTS_PER_TILE * sizeof(GridIndex))

#define SetGridTileBlockEmpty(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_EMPTY_TILE)

#define SetGridTileBlockSolid(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_SOLID_TILE)

class GridTile{
private:
    bool Tile[GRID_ELEMENT_WIDTH][GRID_ELEMENT_HEIGHT];  // Element: true if solid false otherwise
    bool empty;  // true if empty false otherwise
public:
    void setTileElement(int x,int y,bool solid){this->Tile[x][y]=solid;}
    bool getTileElement(int x,int y){return this->Tile[x][y];}
    void setNotEmpty();
    void setEmpty();
    bool isTileAssumedEmpty(){ return  empty; }
    GridTile(bool empty);
};


void initialiseTilesetGrid();

class GridLayer {
private:
    GridTile *GridMap[MAX_HEIGHT][MAX_WIDTH] ;
    Dim totalRows = 0, totalColumns = 0;
    ALLEGRO_BITMAP *dpyBuffer = NULL;
    Rect viewWin{0,0,DISPLAY_W,DISPLAY_H};
    bool dpyChanged = true;
    Dim dpyX = 0, dpyY = 0;
    void Allocate(void) {
        this->dpyBuffer = al_create_bitmap((MAX_WIDTH + 2) * TILE_WIDTH, (MAX_HEIGHT + 2) * TILE_HEIGHT);
    }
    // inside the private section
    void     FilterGridMotionDown (const Rect& r, int* dy) ;
    void     FilterGridMotionUp (const Rect& r, int* dy) ;
    void     FilterGridMotionRight (const Rect& r, int* dx) ;
    void     FilterGridMotionLeft (const Rect& r, int* dx) ;

public:
    ALLEGRO_BITMAP *GetBuffer(){return this->dpyBuffer;}
    void SetGridTile (Dim row, Dim col, GridTile *tile){this->GridMap[row][col] = tile;}
    GridTile *GetGridTile (Dim row, Dim col) { return this->GridMap[row][col]; }
    void Display(ALLEGRO_BITMAP *dest, const Rect& displayArea);
    void SetViewWindow (const Rect& r) { viewWin = r; dpyChanged = true; }
    Dim getRows(){return this->totalRows;}
    Dim getColumns(){return this->totalColumns;}

    GridLayer (unsigned rows, unsigned cols);

};



#endif //CS454_SUPER_MARIO_GAME_TERRAIN_H
