#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/sound.h"
#include "../../../Engine/Include/rendering.h"
#include <filesystem>
extern uint64_t GameTime;

extern ALLEGRO_DISPLAY *window;
extern TileLayer *background,*terrain;

/***************************************
 *  Initialization Functions          *
 **************************************/

void InitializeBitmaps(){
    for (auto const& f : std::filesystem::recursive_directory_iterator(AnimationBitmaps)) {
        if(!std::filesystem::is_directory(f.path()) && f.path().filename() != ".DS_Store") { // Exclude folder as files and .DS_Store file
            BitmapLoader::GetLoader().Store(f.path().filename(), al_load_bitmap(f.path().string().c_str()));
        }
    }
}

void InitializeFilms(){

    for(auto const f :std::filesystem::recursive_directory_iterator(AnimationBitmaps)) {
        if (!std::filesystem::is_directory(f.path()) && f.path().filename() != ".DS_Store") { // Exclude folder as files and .DS_Store file
            ALLEGRO_BITMAP *bitmap = BitmapLoader::GetLoader().Load(f.path().filename());
            if (bitmap == NULL)assert(false);
            int frames;
            int width;
            int height;
            if(  f.path().filename() == GameOver){
                frames = int(al_get_bitmap_width(bitmap) / 256 );
                width = 256;
                height = 232;
            }
            else if(f.path().filename() == TitleScreen ){
                frames = int(al_get_bitmap_width(bitmap) / 1024 );
                width = 1024;
                height = 928;
            }

            else if(f.path().filename() == DownLeft || f.path().filename() == DownRight || f.path().filename() == AttackLeft || f.path().filename() == AttackRight ){
                frames = int(al_get_bitmap_width(bitmap) / 32);
                width = 32;
                height = 32;
            }
            else if(f.path().filename() == Door){
                frames = int(al_get_bitmap_width(bitmap) / 8);
                width = 8;
                height = 48;
            }
            else if(f.path().filename() == Key || f.path().filename() == Candle || f.path().filename() == Fairy || f.path().filename() == Lava){
                frames = 1;
                width = 16;
                height = 16;
            }
            else if(f.path().filename() == Elevator){
                frames = 1;
                width = 32;
                height = 64;
            }
            else if(f.path().filename() == FallingBridge || f.path().filename() == Bot || f.path().filename() == Bubble || f.path().filename() == Enemy16Death ){
                frames = int(al_get_bitmap_width(bitmap) / 16);
                width = 16;
                height = 16;
            }
            else if(f.path().filename() == StalfosAttackLeft || f.path().filename() == StalfosAttackRight) {
                frames = int(al_get_bitmap_width(bitmap) / 32);
                width = 32;
                height = 32;
            }
            else {
                frames = int(al_get_bitmap_width(bitmap) / 16);
                width = 16;
                height = 32;
            }

            std::vector<Rect> boxes = {};
            for (int i = 0; i < frames; i++)
                boxes.push_back({i * width, 0, width, height});
            AnimationFilm *film = new AnimationFilm(bitmap, boxes, f.path().filename());

            AnimationFilmHolder::GetHolder().Store(f.path().filename(), film);

        }
    }
}


void InitializeSprites(){
//    createPauseScreen();
    createTittleScreen();
    createLink();
    createGameOver();

    createEnemiesAndObjects();
}

void InitializeSounds(){
    LoadSounds();
}

void InitializeRendering() {

    if(window == nullptr) {
        window = al_create_display(DISPLAY_W,DISPLAY_H);
        al_set_display_flag(window, ALLEGRO_FULLSCREEN_WINDOW, false);

        al_set_display_icon(window, al_load_bitmap(ICON_FILE_PATH));
    }
    if (background == nullptr)
        background = new TileLayer(MAX_HEIGHT, MAX_WIDTH, al_load_bitmap(TILESET_FILE_PATH), BACKGROUND_CSV_FILE_PATH);
    if (terrain == nullptr)
        terrain = new TileLayer(MAX_HEIGHT, MAX_WIDTH, al_load_bitmap(TILESET_FILE_PATH), TERRAIN_CSV_FILE_PATH);
}
