#include "../../../Engine/Include/rendering.h"

ALLEGRO_DISPLAY *window = nullptr;
Rect DisplayArea{0, 0, DISPLAY_W, DISPLAY_H}; //visible rectangle in screen
TileLayer *background = nullptr, *terrain = nullptr;

/***************************************
 *  Main Loop Rendering Function      *
 **************************************/

void ZeldaII_Rendering() {
    if (inputs.at("F")) {
        inputs["FullScreen"] = !inputs["FullScreen"];
        al_set_display_flag(window, ALLEGRO_FULLSCREEN_WINDOW, inputs["FullScreen"]);
    }

    if (!inputs.at("start"))
        tittle_screen_rendering();
    else
        parapa_palace_level_rendering();
}

void tittle_screen_rendering() {
    al_set_target_backbuffer(window);
    al_clear_to_color(KEY_COLOR);

    int displayWidth = al_get_display_width(window);
    int displayHeight = al_get_display_height(window);

    for (auto i: SpriteManager::GetSingleton().GetDisplayList()) {
        if (i->GetTypeId() == "TitleScreen" && i->IsVisible()) {

            Rect frameBox = AnimationFilmHolder::GetHolder().Load(TitleScreen)->GetFrameBox(i->GetFrame());

            //temp bitmap
            ALLEGRO_BITMAP *tempBitmap = al_create_bitmap(frameBox.w, frameBox.h);

            al_set_target_bitmap(tempBitmap);
            al_clear_to_color(al_map_rgba(0, 0, 0, 0));

            AnimationFilmHolder::GetHolder().Load(TitleScreen)->DisplayFrame(tempBitmap, {0, 0}, i->GetFrame());
            al_set_target_backbuffer(window);

            al_draw_scaled_bitmap(tempBitmap,
                                  0, 0, frameBox.w, frameBox.h, // source bitmap region
                                  0, 0, displayWidth, displayHeight, // target bitmap region
                                  0);

            al_destroy_bitmap(tempBitmap);
        }
    }

    al_flip_display();
}


void parapa_palace_level_rendering() {
    ALLEGRO_BITMAP *tempBuffer;

    // Fetch the full screen dimensions
    int fullScreenWidth = al_get_display_width(window);
    int fullScreenHeight = al_get_display_height(window);

    // Calculate scaling factors based on the full screen size and the base resolution
    float scaleX = fullScreenWidth / 640.0f;
    float scaleY = fullScreenHeight / 480.0f;

    al_clear_to_color(KEY_COLOR);

    //Render terrain and background
    background->Display(al_get_backbuffer(window), DisplayArea);
    terrain->Display(al_get_backbuffer(window), DisplayArea);

    //Render Grid
    if (inputs.at("G")) {
        terrain->GetGrid()->Display(al_get_backbuffer(window), DisplayArea);
    }

    for(auto i : SpriteManager::GetSingleton().GetDisplayList()){
        if(i->GetTypeId() == "Link")
            i->Display(al_get_backbuffer(window),DisplayArea,MakeTileLayerClipper(terrain));
        else if(i->IsVisible() && i->GetTypeId() != "TitleScreen")
            i->Display(al_get_backbuffer(window),DisplayArea,MakeTileLayerClipper(terrain));
    }
    tempBuffer = al_clone_bitmap(al_get_backbuffer(window));
    al_clear_to_color(KEY_COLOR);
    al_draw_scaled_bitmap(tempBuffer,0,0,al_get_bitmap_width(tempBuffer), al_get_bitmap_height(tempBuffer),0,0,
                          DISPLAY_W*2.4, DISPLAY_H*2.4,0);
    // Set up the transformation
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, scaleX, scaleY);
    al_use_transform(&transform);

    al_set_target_backbuffer(window);

    al_flip_display();
    al_unlock_bitmap(al_get_backbuffer(window));
}




