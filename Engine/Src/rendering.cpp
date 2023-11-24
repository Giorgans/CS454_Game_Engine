//
// Created by Georgios Zervos on 8/12/21.
//
#include "../Include/rendering.h"

ALLEGRO_DISPLAY *window = nullptr;
Rect DisplayArea {0,0,DISPLAY_W*2,DISPLAY_H*2};
TileLayer *background= nullptr,*terrain=nullptr;
extern std::map<std::string,bool> inputs;
/** Main render function,
 * subsystem for Game::MainLoopIteration()  */
void Rendering() {
    ALLEGRO_BITMAP *tempBuffer;
    if(window == nullptr){
        window = al_create_display(DISPLAY_W,DISPLAY_H);
        al_set_display_icon(window, al_load_bitmap(ICON_FILE_PATH));
    }
    if (background == nullptr)
        background = new TileLayer(MAX_HEIGHT, MAX_WIDTH, al_load_bitmap(TILESET_FILE_PATH), BACKGROUND_CSV_FILE_PATH);
    if (terrain == nullptr)
        terrain = new TileLayer(MAX_HEIGHT, MAX_WIDTH, al_load_bitmap(TILESET_FILE_PATH), TERRAIN_CSV_FILE_PATH);

    al_set_target_backbuffer(window);
    al_clear_to_color(KEY_COLOR);

    //Render terrain and background
    background->Display(al_get_backbuffer(window), DisplayArea);
    terrain->Display(al_get_backbuffer(window), DisplayArea);
    //Render Grid
    if (inputs.at("G"))
        terrain->GetGrid()->Display(al_get_backbuffer(window), DisplayArea);
    // Render sprites
    for(auto i : SpriteManager::GetSingleton().GetDisplayList()){
        if(i->IsVisible())
            i->Display(al_get_backbuffer(window),DisplayArea,MakeTileLayerClipper(terrain));
    }
    tempBuffer = al_clone_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    al_draw_scaled_bitmap(tempBuffer,0,0,al_get_bitmap_width(tempBuffer), al_get_bitmap_height(tempBuffer),0,0,
                          al_get_bitmap_width(tempBuffer)*2.4, al_get_bitmap_height(tempBuffer)*2.4,0);
    al_flip_display();
    al_unlock_bitmap(al_get_backbuffer(window));
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
    al_draw_scaled_bitmap(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,DISPLAY_W,DISPLAY_H,0);
    al_unlock_bitmap(dest);
}

// Draws a scaled part of bitmap to an area of another bitmap
void BitmapBlitScaledSprite(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    al_set_target_bitmap(dest);
    al_draw_scaled_bitmap(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,src_rect.w,32,0);
    al_unlock_bitmap(dest);
}
