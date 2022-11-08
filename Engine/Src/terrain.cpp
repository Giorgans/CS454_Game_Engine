//
// Created by Georgios Zervos on 18/11/21.
//
#include "../Include/terrain.h"

// Draws the tiles in dpybuffer and blits it in the backbuffer
void TileLayer::Display(ALLEGRO_BITMAP *dest, const Rect &displayArea){
    if(GetBuffer()==nullptr) Allocate();
    if (dpyChanged) {
        al_set_target_bitmap(GetBuffer());
        al_clear_to_color(TRANSPARENT);
        al_unlock_bitmap(GetBuffer());
        auto startCol = DIV_TILE_WIDTH(viewWin.x);
        auto startRow = DIV_TILE_HEIGHT(viewWin.y);
        auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
        auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
        dpyX = MOD_TILE_WIDTH(viewWin.x);
        dpyY = MOD_TILE_WIDTH(viewWin.y);
        dpyChanged = false;
        for (Dim row = startRow; row <= endRow; ++row)
            for (Dim col = startCol; col <= endCol; ++col)
                PutTile(GetBuffer(), MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tileSet,GetTile(row, col));
    }
    BitmapBlitScaled(GetBuffer(),{dpyX,dpyY, viewWin.w,viewWin.h},dest,{0,0});
}

//Gets {x,y} Position of wanted tile in the tile set
Dim TileX (byte index)  { return (index % TILESET_WIDTH)*TILE_WIDTH; }
Dim TileY (byte index)  { return (index / TILESET_HEIGHT)*TILE_HEIGHT; }

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
            if(std::stoi(csv_value)==-1) {
                SetTile(row, col, EMPTY_TILE);
                this->GetGrid()->SetGridTile(row,col,new GridTile(true));
            }
            else{
                SetTile(row,col, std::stoi(csv_value));
                this->GetGrid()->SetGridTile(row,col,new GridTile(false));
            }
            col++;
        }
        row++;
        col=0;
    }
    return true;
}

//Tile layer constructor
TileLayer::TileLayer(Dim rows, Dim cols, ALLEGRO_BITMAP *tileSet,std::string path) {
    Allocate();
    this->tileSet=tileSet;
    al_convert_mask_to_alpha(tileSet,KEY_COLOR);
    this->totalRows=rows;
    this->totalColumns=cols;
    this->grid = new GridLayer(rows,cols);
    if(!ReadText(path)) assert(0);
}

void TileLayer::Scroll (float dx, float dy){
    auto w = GetViewWindow();
    w.x+=dx;
    w.y+=dy;
    SetViewWindow(w);
    this->GetGrid()->SetViewWindow(w);

}

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
    al_draw_scaled_bitmap(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,DISPLAY_W*2,DISPLAY_H*2,0);
    al_unlock_bitmap(dest);
}




/*************************** Grid implemetation  ********************************/

GridTile::GridTile(bool empty){
    if(empty)
        this->setEmpty();
    else
        this->setNotEmpty();
}
void GridTile::setNotEmpty() {
    this->empty = false;
    for(int i = 0 ; i < GRID_ELEMENT_WIDTH ; i++ )
        for(int j = 0 ; j < GRID_ELEMENT_HEIGHT ; j++ )
            Tile[i][j] = true;
}

void GridTile::setEmpty() {
    this->empty = true;
    for(int i = 0 ; i < GRID_ELEMENT_WIDTH ; i++ )
        for(int j = 0 ; j < GRID_ELEMENT_HEIGHT ; j++ )
            Tile[i][j] = false;
}

GridLayer::GridLayer (unsigned rows, unsigned cols){
    for(auto i = 0 ; i<MAX_HEIGHT ; i++)
        for(auto j = 0 ; j < MAX_WIDTH ; j++)
            GridMap[i][j] = new GridTile(true);
     for(auto row=0 ; row < rows ; row++)
        for(auto col=0 ; col < cols ; col++)
            this->SetGridTile(row,col, NULL);
}

void GridLayer::Display(ALLEGRO_BITMAP *dest, const Rect& displayArea){
    if(GetBuffer() == nullptr) Allocate();
    if (dpyChanged) {
        al_set_target_bitmap(GetBuffer());
        al_clear_to_color(TRANSPARENT);
        al_unlock_bitmap(GetBuffer());
        auto startCol = DIV_TILE_WIDTH(viewWin.x);
        auto startRow = DIV_TILE_HEIGHT(viewWin.y);
        auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
        auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
        dpyX = MOD_TILE_WIDTH(viewWin.x);
        dpyY = MOD_TILE_WIDTH(viewWin.y);
        dpyChanged = false;
        for (Dim row = startRow; row <= endRow; ++row)
            for (Dim col = startCol; col <= endCol; ++col)
                if( (GetGridTile(row,col) != nullptr) && (!GetGridTile(row,col)->isTileAssumedEmpty()) ) {
                    al_set_target_bitmap(GetBuffer());
                    // draws grid of the solid Tile
                    al_draw_rectangle(MUL_TILE_WIDTH(col - startCol) ,
                                      MUL_TILE_HEIGHT(row - startRow),
                                      MUL_TILE_WIDTH(col - startCol)  + TILE_WIDTH  ,
                                      MUL_TILE_HEIGHT(row - startRow) + TILE_HEIGHT ,
                                      WHITE, 1.5);
                    // draws the elements of the solid Tile
                    for(auto elX = 0 ; elX<GRID_ELEMENT_WIDTH ; elX++)
                        for(auto elY = 0 ; elY<GRID_ELEMENT_HEIGHT ; elY++)
                            al_draw_rectangle(MUL_TILE_WIDTH(col - startCol)  + elX*GRID_ELEMENT_WIDTH ,
                                              MUL_TILE_HEIGHT(row - startRow) + elY*GRID_ELEMENT_HEIGHT,
                                              (MUL_TILE_WIDTH(col - startCol)  + elX*GRID_ELEMENT_WIDTH)  + GRID_ELEMENT_WIDTH ,
                                              (MUL_TILE_HEIGHT(row - startRow) + elY*GRID_ELEMENT_HEIGHT) + GRID_ELEMENT_HEIGHT ,
                                              WHITE, 1);

                    al_unlock_bitmap(GetBuffer());
                }
    }
    BitmapBlitScaled(GetBuffer(),{dpyX,dpyY, viewWin.w,viewWin.h},dest,{0,0});
}


/*
void GridLayer::FilterGridMotion (const Rect& r, int* dx, int* dy)  {
    assert( abs(*dx) <= GRID_ELEMENT_WIDTH && abs(*dy) <= GRID_ELEMENT_HEIGHT );
    // try horizontal move
    if (*dx < 0) FilterGridMotionLeft(r, dx);
    else if (*dx > 0)
        FilterGridMotionRight(r, dx);
    // try vertical move
    if (*dy < 0) FilterGridMotionUp(r, dy);
    else if (*dy > 0)
        FilterGridMotionDown(r, dy);
}
*/
