#include "../../../Engine/Include/rendering.h"

ALLEGRO_DISPLAY *window = nullptr;
Rect DisplayArea {0,0,DISPLAY_W*2,DISPLAY_H*2};
extern std::map<std::string,bool> inputs;
extern FrameRangeAnimator *TitleScreenAnimator;
TileLayer *background= nullptr,*terrain=nullptr;
ALLEGRO_BITMAP *titlescreen= nullptr;

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
    if(titlescreen == nullptr){
        titlescreen = al_create_bitmap(DISPLAY_W,DISPLAY_H);
    }
    TitleScreenAnimations();
    auto frame = TitleScreenAnimator->GetCurrFrame();
    Rect framebox = AnimationFilmHolder::GetHolder().GetFilm(TitleScreen)->GetFrameBox(frame);
    
    al_set_target_bitmap(titlescreen);
    BitmapBlit(AnimationFilmHolder::GetHolder().GetFilm(TitleScreen)->GetBitmap(),framebox,titlescreen,{0,0});
    al_unlock_bitmap(titlescreen);

    al_set_target_backbuffer(window);
    al_clear_to_color(BLACK);
    al_draw_scaled_bitmap(titlescreen,0,0,
                          al_get_bitmap_width(titlescreen),
                          al_get_bitmap_height(titlescreen),0,0,
                          DISPLAY_W*2.5,
                          DISPLAY_H*2.1,0);
    al_flip_display();
    al_clear_to_color(BLACK);
    al_unlock_bitmap(al_get_backbuffer(window));
}


void parapa_palace_level_rendering(){
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