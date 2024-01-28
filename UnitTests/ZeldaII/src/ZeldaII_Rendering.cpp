#include "../../../Engine/Include/rendering.h"

ALLEGRO_DISPLAY *window = nullptr;
Rect DisplayArea {0,0,DISPLAY_W*2,DISPLAY_H*2};
TileLayer *background=nullptr,*terrain=nullptr;

/***************************************
 *  Main Loop Rendering Function      *
 **************************************/

void ZeldaII_Rendering() {
    if(!inputs.at("start"))
        tittle_screen_rendering();
    else
        parapa_palace_level_rendering();

}

void tittle_screen_rendering(){

    if(window == nullptr){
        window = al_create_display(DISPLAY_W,DISPLAY_H);
        al_set_display_icon(window, al_load_bitmap(ICON_FILE_PATH));
    }

    al_set_target_backbuffer(window);
    al_clear_to_color(KEY_COLOR);
    for(auto i : SpriteManager::GetSingleton().GetDisplayList()){
        if(i->GetTypeId() == "TitleScreen" && i->IsVisible())
            AnimationFilmHolder::GetHolder().Load(TitleScreen)->DisplayFrame(al_get_backbuffer(window),{DisplayArea.x ,DisplayArea.y},i->GetFrame());
    }
    auto tempBuffer = al_clone_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    al_draw_scaled_bitmap(tempBuffer,0,0,al_get_bitmap_width(tempBuffer), al_get_bitmap_height(tempBuffer),0,0,
                          al_get_bitmap_width(tempBuffer)*2.5, al_get_bitmap_height(tempBuffer)*2.1,0);
    al_flip_display();
    al_unlock_bitmap(al_get_backbuffer(window));
}


void parapa_palace_level_rendering(){
    ALLEGRO_BITMAP *tempBuffer;
    if(window == nullptr){
        window = al_create_display(DISPLAY_W,DISPLAY_H);
        al_set_display_icon(window, al_load_bitmap(ICON_FILE_PATH));
    }
    else {
        al_set_target_backbuffer(window);
        al_clear_to_color(KEY_COLOR);
        al_unlock_bitmap(al_get_backbuffer(window));
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
        if(i->GetTypeId() == "Link")
            i->Display(al_get_backbuffer(window),DisplayArea,MakeTileLayerClipper(terrain));
        if(i->IsVisible() && i->GetTypeId() != "TitleScreen")
            i->Display(al_get_backbuffer(window),DisplayArea,MakeTileLayerClipper(terrain));
    }
    tempBuffer = al_clone_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    al_draw_scaled_bitmap(tempBuffer,0,0,al_get_bitmap_width(tempBuffer), al_get_bitmap_height(tempBuffer),0,0,
                          al_get_bitmap_width(tempBuffer)*2.4, al_get_bitmap_height(tempBuffer)*2.4,0);
    al_flip_display();
    al_unlock_bitmap(al_get_backbuffer(window));

}