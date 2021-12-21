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
    //al_lock_bitmap(al_get_backbuffer(window), ALLEGRO_PIXEL_FORMAT_ANY, 0);
    al_set_target_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    //al_draw_scaled_bitmap(background_bitmap,viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_draw_scaled_bitmap(background->GetBitmap(),viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_draw_scaled_bitmap(terrain->GetBitmap(),viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_unlock_bitmap(al_get_backbuffer(window));
    al_flip_display();
    al_rest(10);
}

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
    BitmapBlit(dpyBuffer,{ this->dpyX, this->dpyY , viewWin.w, viewWin.h },dest,{ displayArea.x, displayArea.y });
}

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

byte MakeIndex (byte row, byte col ) { return  (col << COL_SHIFT) | row; }
Index MakeIndex2 (byte row, byte col){ return (MUL_TILE_WIDTH(col) << TILEX_SHIFT) | MUL_TILE_HEIGHT(row); }
byte GetCol (byte index)    { return index >> COL_SHIFT; }
byte GetRow (byte index)    { return index & ROW_MASK; }
Dim TileX (byte index)  { return GetCol(index) * TILESET_WIDTH; }
Dim TileY (byte index)  { return GetRow(index) * TILESET_HEIGHT; }
Dim TileX2 (byte index) { return MUL_TILE_WIDTH(GetCol(index)); }
Dim TileY2 (byte index) { return MUL_TILE_HEIGHT(GetRow(index)); }
Dim TileX3 (Index index) { return index >> TILEX_SHIFT; }
Dim TileY3 (Index index) { return index & TILEY_MASK; }
void SetTile (TileMap* m, Dim col, Dim row, Index index) { (*m)[row][col] = index; }
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile) {
    if(tile != EMPTY_TILE)
        BitmapBlit(tiles,  { (tile%TILESET_WIDTH)*TILE_WIDTH, (tile/TILESET_HEIGHT)*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT }, dest,{ x, y });
}
Index GetTile (const TileMap* m, Dim col, Dim row) { return (*m)[row][col]; }
//void WriteBinMap (const TileMap* m, FILE* fp)   { fwrite(m, sizeof(TileMap), 1, fp); }
//bool ReadBinMap (TileMap* m, FILE* fp)  { /* binary formatted read, like descent parsing */ }
void WriteTextMap (const TileMap*, FILE* fp) { /* custom write in text format */ }

void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    //auto lock = al_lock_bitmap(dest,ALLEGRO_PIXEL_FORMAT_ANY,0);
    al_set_target_bitmap(dest);
    al_draw_bitmap_region(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,0);
    al_unlock_bitmap(dest);
}
/*
void Scroll (Rect* DisplayArea, int dx, int dy)
{ DisplayArea->x += dx; DisplayArea->y += dy; }
bool CanScrollHoriz (const Rect& DisplayArea, int dx) {
    return DisplayArea.x >= -dx && (DisplayArea.x + DisplayArea.w + dx) <= GetMapPixelWidth();
}
bool CanScrollVert (const Rect& DisplayArea, int dy) {
    return DisplayArea.y >= -dy &&
           (DisplayArea.y + DisplayArea.h + dy) <= GetMapPixelHeight();
}
*/

/*
using BitmapAccessFunctor = std::function<void(ALLEGRO_COLOR*)>;

void BitmapAccessPixels (ALLEGRO_BITMAP *bmp, const BitmapAccessFunctor & f) {

    auto result = al_lock_bitmap(bmp,ALLEGRO_LOCK_WRITEONLY,0);
    assert(result);
    auto mem = BitmapGetMemory(bmp);
    auto offset = BitmapGetLineOffset(bmp);
    for (auto y = al_get_bitmap_height(bmp); y--; ) {
        auto buff = mem;
        for (auto x = al_get_bitmap_width(bmp); x--; ) {
            f(buff);
            buff += GetDepth();
        }
        mem += offset;

    }
    al_unlock_bitmap(bmp);
}
*/
