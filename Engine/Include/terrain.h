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
// Moving tiles
#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
//#define MOD_TILE_HEIGHT(i)((i)&15)

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
    bool CanScrollHoriz (float dx){
        //Checking if the level has ended
        if(GetViewWindow().x + dx == (getCols()*TILE_WIDTH - 20*TILE_WIDTH)) return true;
        else return false;
    }
    //void Save (const std::string& path) ;
    //bool Load (const std::string& path);
    bool ReadText (std::string path);
    TileLayer (Dim rows, Dim cols, ALLEGRO_BITMAP *tileSet,std::string path);
    ~TileLayer (){
        al_destroy_bitmap(GetBuffer());
    }
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
    bool empty;  // true if empty false otherwise
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
        this->dpyBuffer = al_create_bitmap(MAX_WIDTH  * TILE_WIDTH, MAX_HEIGHT  * TILE_HEIGHT);
    }
    // inside the private section
    //void     FilterGridMotionDown (const Rect& r, int* dy) ;
   // void     FilterGridMotionUp (const Rect& r, int* dy) ;
   // void     FilterGridMotionRight (const Rect& r, int* dx) ;
   // void     FilterGridMotionLeft (const Rect& r, int* dx) ;

public:
    ALLEGRO_BITMAP *GetBuffer(){return this->dpyBuffer;}
    void SetGridTile (Dim row, Dim col, GridTile *tile){this->GridMap[row][col] = tile;}
    GridTile *GetGridTile (Dim row, Dim col) { return this->GridMap[row][col]; }
    void Display(ALLEGRO_BITMAP *dest, const Rect& displayArea);
    void SetViewWindow (const Rect& r) { viewWin = r; dpyChanged = true; }

    GridLayer (unsigned rows, unsigned cols);
    ~GridLayer(){ al_destroy_bitmap(GetBuffer());}

};



#endif //CS454_SUPER_MARIO_GAME_TERRAIN_H
