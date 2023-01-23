//
// Created by Georgios Zervos on 8/12/21.
//
#include "../Include/rendering.h"

ALLEGRO_DISPLAY *window = nullptr;
Rect DisplayArea {0,0,DISPLAY_W*2,DISPLAY_H*2};
TileLayer *background= nullptr,*terrain=nullptr;
bool displayGrid = false;

/** Main render function,
 * subsystem for Game::MainLoopIteration()  */
void Rendering() {
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
    if (displayGrid)
        terrain->GetGrid()->Display(al_get_backbuffer(window), DisplayArea);
    // Render sprites
    for(auto i : SpriteManager::GetSingleton().GetDisplayList()){
        if(i->IsVisible())
            i->Display(al_get_backbuffer(window),DisplayArea,MakeTileLayerClipper(terrain));
    }

    al_flip_display();
    al_unlock_bitmap(al_get_backbuffer(window));
}

