//
// Created by Georgios Zervos on 8/12/21.
//
#include "../Include/rendering.h"
extern ALLEGRO_DISPLAY *window;
Rect DisplayArea {0,0,DISPLAY_W*2,DISPLAY_H*2};
TileLayer *background= nullptr,*terrain=nullptr;

/** Main render function,
 * subsystem for Game::MainLoopIteration()  */
void Rendering(void){
    if(background==nullptr)
        background = new TileLayer(MAX_HEIGHT,MAX_WIDTH, al_load_bitmap(TILESET_FILE_PATH),BACKGROUND_CSV_FILE_PATH);
    if(terrain==nullptr)
        terrain = new TileLayer(MAX_HEIGHT,MAX_WIDTH, al_load_bitmap(TILESET_FILE_PATH),TERRAIN_CSV_FILE_PATH);

    al_set_target_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    background->Display(al_get_backbuffer(window),DisplayArea);
    terrain->Display(al_get_backbuffer(window),DisplayArea);
    al_unlock_bitmap(al_get_backbuffer(window));
    al_flip_display();
}

// Draws the tiles in dpybuffer and blits it in the backbuffer
void TileLayer::Display(ALLEGRO_BITMAP *dest, const Rect &displayArea){
    Allocate();
    if (dpyChanged) {
        auto startCol = DIV_TILE_WIDTH(viewWin.x);
        auto startRow = DIV_TILE_HEIGHT(viewWin.y);
        auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
        auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
        dpyX = MOD_TILE_WIDTH(viewWin.x);
        dpyY = MOD_TILE_WIDTH(viewWin.y);
        dpyChanged = false;
        for (Dim row = startRow; row <= endRow; ++row)
            for (Dim col = startCol; col <= endCol; ++col)
                PutTile(dpyBuffer, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tileSet,GetTile(row, col));
     }
    BitmapBlitScaled(dpyBuffer,{dpyX,dpyY, viewWin.w,viewWin.h},dest,{displayArea.x,displayArea.y});
    al_destroy_bitmap(dpyBuffer);
}

// Reads csv file and stores the indexes in the tile map
bool TileLayer::ReadText(std::string path) {
    std::string csv_value,line;
    Dim col=0,row=0;
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) return false;
    while(std::getline(file, line))
    {
        std::stringstream str(line);
        while(getline(str, csv_value, ',')){
            if(std::stoi(csv_value)==-1)
                SetTile(row,col, EMPTY_TILE);
            else
                SetTile(row,col, std::stoi(csv_value));

            col++;
        }
        row++;
        col=0;
    }
    return true;
}

//Tile layer constructor
TileLayer::TileLayer(Dim rows, Dim cols, ALLEGRO_BITMAP *tileSet, std::string path) {
        Allocate();
        this->tileSet=tileSet;
        al_convert_mask_to_alpha(tileSet,KEY_COLOR);
        this->totalRows=rows;
        this->totalColumns=cols;
        if(!ReadText(path)) assert(0);
}

void TileLayer::Scroll (float dx, float dy){
    auto w = GetViewWindow();
    w.x+=dx;
    w.y+=dy;
    SetViewWindow(w);

}

//Gets {x,y} Position of wanted tile in the tile set
Dim TileX (byte index)  { return (index % TILESET_WIDTH)*TILE_WIDTH; }
Dim TileY (byte index)  { return (index / TILESET_HEIGHT)*TILE_HEIGHT; }

// Draws tile to specific area of a bitmap
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile) {
        if(tile!=EMPTY_TILE)
            BitmapBlit(tiles,  { TileX(tile), TileY(tile) , TILE_WIDTH, TILE_HEIGHT }, dest,{ x, y });
}

// Draws a part of bitmap to an area of another bitmap
void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    al_set_target_bitmap(dest);
    al_draw_bitmap_region(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,0);
    al_unlock_bitmap(dest);
}

// Draws a scaled part of bitmap to an area of another bitmap
void BitmapBlitScaled(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    al_set_target_bitmap(dest);
    al_draw_scaled_bitmap(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,DisplayArea.w,DisplayArea.h,0);
    al_unlock_bitmap(dest);
}
