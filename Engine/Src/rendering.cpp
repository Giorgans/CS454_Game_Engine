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
    TileMap background,terrain;
    ALLEGRO_BITMAP *terrain_bitmap = al_create_bitmap(MAX_WIDTH*TILE_WIDTH,MAX_HEIGHT*TILE_HEIGHT);
    ALLEGRO_BITMAP *background_bitmap = al_create_bitmap(MAX_WIDTH*TILE_WIDTH,MAX_HEIGHT*TILE_HEIGHT);
    if(ReadTextMap(&background, BACKGROUND_CSV_FILE_PATH))
        TileBackgroundDisplay(&background, background_bitmap, viewWin, DisplayArea);
    if(ReadTextMap(&terrain, TERRAIN_CSV_FILE_PATH))
        TileTerrainDisplay(&terrain, terrain_bitmap, viewWin, DisplayArea);
    //al_lock_bitmap(al_get_backbuffer(window), ALLEGRO_PIXEL_FORMAT_ANY, 0);
    al_set_target_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    //al_draw_scaled_bitmap(background_bitmap,viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_draw_scaled_bitmap(background_bitmap,viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_draw_scaled_bitmap(terrain_bitmap,viewWin.x,viewWin.y,viewWin.w,viewWin.h,DisplayArea.x,DisplayArea.y,DisplayArea.w,DisplayArea.h,0);
    al_unlock_bitmap(al_get_backbuffer(window));
    al_flip_display();
    al_rest(10);
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
bool ReadTextMap (TileMap *m, std::string path)
{
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
                SetTile(m,y,x, EMPTY_TILE);
            else
                SetTile(m,y,x, std::stoi(csv_value));

            x++;
        }
        y++;
        x=0;
    }
    return true;
}

ALLEGRO_BITMAP *BackdpyBuffer = nullptr;
Dim bdpyX = 0, bdpyY = 0;
Point BackviewPosCached { -1, -1 };
void TileBackgroundDisplay (TileMap *map, ALLEGRO_BITMAP *dest, const Rect& viewWin, const Rect& displayArea) {
    if(BackdpyBuffer == nullptr) BackdpyBuffer = al_create_bitmap(MUL_TILE_WIDTH(MAX_WIDTH), MUL_TILE_HEIGHT(MAX_HEIGHT));
    ALLEGRO_BITMAP *tileset = al_load_bitmap(TILESET_FILE_PATH);
    if (BackviewPosCached.x != viewWin.x || BackviewPosCached.y != viewWin.y) {
        auto startCol = DIV_TILE_WIDTH(viewWin.x);
        auto startRow = DIV_TILE_HEIGHT(viewWin.y);
        auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
        auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
        bdpyX = MOD_TILE_WIDTH(viewWin.x);
        bdpyY = MOD_TILE_WIDTH(viewWin.y);
        BackviewPosCached.x = viewWin.x, BackviewPosCached.y = viewWin.y;
        for (Dim row = startRow; row <= endRow; ++row)
            for (Dim col = startCol; col <= endCol; ++col)
                PutTile(BackdpyBuffer, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tileset,GetTile(map, row, col));
    }
    BitmapBlit(BackdpyBuffer,{ bdpyX, bdpyY , viewWin.w, viewWin.h },dest,{ displayArea.x, displayArea.y });
}

ALLEGRO_BITMAP *dpyBuffer = nullptr;
Dim dpyX = 0, dpyY = 0;
Point viewPosCached { -1, -1 };
void TileTerrainDisplay (TileMap *map, ALLEGRO_BITMAP *dest, const Rect& viewWin, const Rect& displayArea) {
    if(dpyBuffer == nullptr) dpyBuffer = al_create_bitmap(MUL_TILE_WIDTH(MAX_WIDTH), MUL_TILE_HEIGHT(MAX_HEIGHT));
    ALLEGRO_BITMAP *tileset = al_load_bitmap(TILESET_FILE_PATH);
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
                PutTile(dpyBuffer, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tileset,GetTile(map, row, col));
    }
    BitmapBlit(dpyBuffer,{ dpyX, dpyY , viewWin.w, viewWin.h },dest,{ displayArea.x, displayArea.y });
}

void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    //auto lock = al_lock_bitmap(dest,ALLEGRO_PIXEL_FORMAT_ANY,0);
    al_set_target_bitmap(dest);
    al_draw_bitmap_region(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,0);
    al_unlock_bitmap(dest);
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
/*
void Scroll (Rect* viewWin, int dx, int dy)
{ viewWin->x += dx; viewWin->y += dy; }
bool CanScrollHoriz (const Rect& viewWin, int dx) { return viewWin.x >= -dx &&
                                                           (viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}
bool CanScrollVert (const Rect& viewWin, int dy) {
    return viewWin.y >= -dy &&
           (viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}


*/