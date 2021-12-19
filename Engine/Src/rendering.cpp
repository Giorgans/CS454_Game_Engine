//
// Created by Georgios Zervos on 8/12/21.
//
#include "../Include/rendering.h"
extern ALLEGRO_DISPLAY *window;

ALLEGRO_BITMAP *dpyBuffer = nullptr;
Point viewPosCached { -1, -1 };
Dim dpyX = 0, dpyY = 0;

/** Main render function,
 * subsystem for Game::MainLoopIteration()  */

void Rendering(void){
    Rect viewWin{0,0,DISPLAY_W,DISPLAY_H};
    ALLEGRO_BITMAP *background = nullptr;
    ALLEGRO_BITMAP *terrain = nullptr;
    //al_lock_bitmap(al_get_backbuffer(window), ALLEGRO_PIXEL_FORMAT_ANY, 0);
    al_set_target_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    al_draw_scaled_bitmap(dpyBuffer,0,0,DISPLAY_W,DISPLAY_H,0,0,2.5*DISPLAY_W,2*DISPLAY_H,0);
    al_unlock_bitmap(al_get_backbuffer(window));

    al_flip_display();
}


byte MakeIndex (byte row, byte col ) { return (col << COL_SHIFT) | row; }
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
void PutTile (ALLEGRO_BITMAP *dest, Dim x, Dim y, ALLEGRO_BITMAP *tiles, Index tile) {  BitmapBlit(tiles, Rect { TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT }, dest, Point{ x, y }); }
Index GetTile (const TileMap* m, Dim col, Dim row) { return (*m)[row][col]; }
void WriteBinMap (const TileMap* m, FILE* fp)   { fwrite(m, sizeof(TileMap), 1, fp); }
bool ReadBinMap (TileMap* m, FILE* fp)  { /* binary formatted read, like descent parsing */ }
void WriteTextMap (const TileMap*, FILE* fp) { /* custom write in text format */ }
bool ReadTextMap (TileMap* m, FILE* fp)
{
    /* parsing... */
    return true;
}

void TileTerrainDisplay (TileMap* map, ALLEGRO_BITMAP *dest, const Rect& viewWin, const Rect& displayArea) {
    if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
        auto startCol = DIV_TILE_WIDTH(viewWin.x);
        auto startRow = DIV_TILE_HEIGHT(viewWin.y);
        auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
        auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.y - 1);
        dpyX = MOD_TILE_WIDTH(viewWin.x);
        dpyY = MOD_TILE_WIDTH(viewWin.y);
        viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;
        for (Dim row = startRow; row <= endRow; ++row)
            for (Dim col = startCol; col <= endCol; ++col)
                PutTile(dpyBuffer, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), al_load_bitmap(TILESET_FILE_PATH),GetTile(map, col, row));
    }
    BitmapBlit(dpyBuffer,{ dpyX, dpyY , viewWin.w, viewWin.h },dest,{ displayArea.x, displayArea.y });

}

void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    ALLEGRO_COLOR pixel;
    auto lock = al_lock_bitmap(src,ALLEGRO_LOCK_WRITEONLY,0);
    al_set_target_bitmap(dest);
    for( int i=0 ; i<TILE_WIDTH ; i++ )
        for( int j=0 ; j<TILESET_HEIGHT ; j++ )
            al_put_pixel(dest_point.x,dest_point.y,al_get_pixel(src,src_rect.x+i,src_rect.y+j));


    al_unlock_bitmap(src);
}



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

void Scroll (Rect* viewWin, int dx, int dy)
{ viewWin->x += dx; viewWin->y += dy; }
bool CanScrollHoriz (const Rect& viewWin, int dx) { return viewWin.x >= -dx &&
                                                           (viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}
bool CanScrollVert (const Rect& viewWin, int dy) {
    return viewWin.y >= -dy &&
           (viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}


