//
// Created by Georgios Zervos on 8/12/21.
//
#include "../Include/rendering.h"
extern ALLEGRO_DISPLAY *window;
Rect viewWin{0,0,DISPLAY_W,DISPLAY_H };
Rect DisplayArea {0,0,DISPLAY_W*2,DISPLAY_H*2};


/** Main render function,
 * subsystem for Game::MainLoopIteration()  */
void Rendering(void){
    TileLayer *background = new TileLayer(MAX_WIDTH,MAX_HEIGHT, al_load_bitmap(TILESET_FILE_PATH),BACKGROUND_CSV_FILE_PATH);
    TileLayer *terrain = new TileLayer(MAX_WIDTH,MAX_HEIGHT, al_load_bitmap(TILESET_FILE_PATH),TERRAIN_CSV_FILE_PATH);

    al_set_target_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    al_draw_scaled_bitmap(background->GetBitmap(),viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_draw_scaled_bitmap(terrain->GetBitmap(),viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_unlock_bitmap(al_get_backbuffer(window));

    al_flip_display();
    al_rest(10);
}

// Draws the tiles in dpybuffer
void TileLayer::Display(ALLEGRO_BITMAP *dest, const Rect &displayArea){
    if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
        auto startCol = DIV_TILE_WIDTH(viewWin.x);
        auto startRow = DIV_TILE_HEIGHT(viewWin.y);
        auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
        auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
        dpyX = MOD_TILE_WIDTH(viewWin.x);
        dpyY = MOD_TILE_WIDTH(viewWin.y);
        viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;
        for (Dim row = startRow; row <= endRow; ++row)
            for (Dim col = startCol; col <= endCol; ++col)
                PutTile(dpyBuffer, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tileSet,GetTile(row, col));
    }
}

// Reads csv file and stores the indexes in the tile map
bool TileLayer::ReadText(std::string path) {
    std::string csv_value,line;
    Dim x=0,y=0;
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) return false;
    while(std::getline(file, line))
    {
        std::stringstream str(line);
        while(getline(str, csv_value, ',')){
            if(std::stoi(csv_value)==-1)
                SetTile(y,x, EMPTY_TILE);
            else
                SetTile(y,x, std::stoi(csv_value));

            x++;
        }
        y++;
        x=0;
    }
    return true;
}

TileLayer::TileLayer(Dim rows, Dim cols, ALLEGRO_BITMAP *tileSet, std::string path) {
        Allocate();
        this->tileSet=tileSet;
        this->totalRows=rows;
        this->totalColumns=cols;
        if(ReadText(path)) Display(this->dpyBuffer,viewWin);
}

//Gets {x,y} Position of wanted tile in the tile set
Dim TileX (byte index)  { return (index % TILESET_WIDTH)*TILE_WIDTH; }
Dim TileY (byte index)  { return (index / TILESET_HEIGHT)*TILE_HEIGHT; }
// Draws tile to specific area of a bitmap
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile) {
    if(tile != EMPTY_TILE)
        BitmapBlit(tiles,  { TileX(tile), TileY(tile) , TILE_WIDTH, TILE_HEIGHT }, dest,{ x, y });
}

// Draws a part of bitmap to an area of another bitmap
void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    al_set_target_bitmap(dest);
    al_draw_bitmap_region(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,0);
    al_unlock_bitmap(dest);
}

