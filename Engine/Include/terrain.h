//
// Created by Georgios Zervos on 18/11/21.
//

#ifndef CS454_SUPER_MARIO_GAME_TERRAIN_H
#define CS454_SUPER_MARIO_GAME_TERRAIN_H

#include "../paths.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#define KEY_COLOR al_map_rgb(0,0,1)
#define WHITE al_map_rgb(255, 255, 255)
#define TRANSPARENT al_map_rgba(0,0,0,0)
#define DISPLAY_W 640
#define DISPLAY_H 480
#define TILESET_WIDTH 16
#define TILESET_HEIGHT 16
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define EMPTY_TILE 40
//Max storage of tile map
#define MAX_WIDTH 481
#define MAX_HEIGHT 46

// Moving tiles
#define	TILEX_MASK	0xFF00
#define	TILEX_SHIFT	8
#define	TILEY_MASK	0x00FF

#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define ZELDA_STARTING_POINT_X MUL_TILE_WIDTH(64)
#define ZELDA_STARTING_POINT_Y MUL_TILE_HEIGHT(3)
#define LINK_STARTING_POINT_X MUL_TILE_WIDTH(66)
#define LINK_STARTING_POINT_Y MUL_TILE_HEIGHT(12)

#define DIV_GRID_ELEMENT_WIDTH(i) ((i)>>2)
#define DIV_GRID_ELEMENT_HEIGHT(i) ((i)>>2)
#define MUL_GRID_ELEMENT_WIDTH(i) ((i)<<2)
#define MUL_GRID_ELEMENT_HEIGHT(i) ((i)<<2)
#define MAX_PIXEL_WIDTH MUL_TILE_WIDTH(MAX_WIDTH)
#define MAX_PIXEL_HEIGHT MUL_TILE_HEIGHT(MAX_HEIGHT

typedef unsigned short Dim;
struct Rect { int x, y, w, h; };
struct Point { int x, y; };
typedef unsigned char byte;
typedef unsigned short Index;
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile);
void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
void BitmapBlitScaled(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
void BitmapBlitScaledSprite(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
Dim TileX (byte index);
Dim TileY (byte index);
Dim TileX3 (Index index);
Dim TileY3 (Index index);


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
    void Allocate() {
        this->dpyBuffer = al_create_bitmap((MAX_WIDTH + 2) * TILE_WIDTH, (MAX_HEIGHT + 2) * TILE_HEIGHT);
    }
public:
    ALLEGRO_BITMAP *GetBuffer(){return this->dpyBuffer;}
    GridLayer *GetGrid(){return this->grid;}
    void SetTile (Dim row,Dim col, Index index) { this->map[row][col] = index; }
    Index GetTile (Dim row,Dim col) { return this->map[row][col]; }
    const Rect& GetViewWindow () const { return viewWin; }
    void SetViewWindow (const Rect& r) { viewWin = r; dpyChanged = true; }
    void Display (ALLEGRO_BITMAP *dest, const Rect& displayArea);
    void Scroll (float dx, float dy);
    Dim getCols(){return this->totalColumns;}
    //void Save (const std::string& path) ;
    //bool Load (const std::string& path);
    bool ReadText (std::string path);
    TileLayer (Dim rows, Dim cols, ALLEGRO_BITMAP *tileSet,std::string path);
    ~TileLayer (){
        al_destroy_bitmap(GetBuffer());
    };
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

class GridTile{
private:
    bool Tile[GRID_ELEMENT_WIDTH][GRID_ELEMENT_HEIGHT];  // Element: true if solid false otherwise
    bool empty = false;  // true if empty false otherwise
public:
    void setTileElement(int x,int y,bool solid){this->Tile[x][y]=solid;}
    bool getTileElement(int x,int y){return this->Tile[x][y];}
    void setNotEmpty();
    void setEmpty();
    bool isTileAssumedEmpty() const { return  empty; }
    GridTile(bool empty);
};


class GridLayer {
private:
    GridTile *GridMap[MAX_HEIGHT][MAX_WIDTH] ;
    ALLEGRO_BITMAP *dpyBuffer = nullptr;
    Rect viewWin{0,0,DISPLAY_W,DISPLAY_H};
    bool dpyChanged = true;
    Dim dpyX = 0, dpyY = 0;
    void Allocate() {
        this->dpyBuffer = al_create_bitmap((MAX_WIDTH + 2) * TILE_WIDTH, (MAX_HEIGHT + 2) * TILE_HEIGHT);
    }
    // inside the private section

    //void     FilterGridMotionDown (const Rect& r, int* dy) const;
    void     FilterGridMotionUp (const Rect& r, int* dy) ;

public:
    void     FilterGridMotionRight (const Rect& r, int* dx) ;
    void     FilterGridMotionLeft (const Rect& r, int* dx) ;

    bool CanPassGridTile (Dim col, Dim row) const // i.e. checks if flags set
    { return GridMap[row][col]->isTileAssumedEmpty(); }
    bool IsOnSolidGround (const Rect& r) const { // will need later for gravity
        int dy = 1; // down 1 pixel
        //FilterGridMotionDown(r, &dy);
        return dy == 0; // if true IS attached to solid ground
    }
    ALLEGRO_BITMAP *GetBuffer(){return this->dpyBuffer;}
    void SetGridTile (Dim row, Dim col, GridTile *tile){this->GridMap[row][col] = tile;}
    GridTile *GetGridTile (Dim row, Dim col) { return this->GridMap[row][col]; }
    void Display(ALLEGRO_BITMAP *dest, const Rect& displayArea);
    void SetViewWindow (const Rect& r) { viewWin = r; dpyChanged = true; }
    void FilterGridMotion (const Rect& r, int* dx, int* dy);
    GridLayer (unsigned rows, unsigned cols);
    ~GridLayer(){ al_destroy_bitmap(GetBuffer());}

};


#endif //CS454_SUPER_MARIO_GAME_TERRAIN_H