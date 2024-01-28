#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/sound.h"
#include "../../../Engine/Include/rendering.h"
#include <filesystem>
extern uint64_t GameTime;



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
            if(f.path().filename() == TitleScreen ){
                frames = int(al_get_bitmap_width(bitmap) / 256 );
                width = 256;
                height = 232;
            }
            else if(f.path().filename() == DownLeft || f.path().filename() == DownRight || f.path().filename() == AttackLeft || f.path().filename() == AttackRight ){
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
    createTittleScreen();
    createLink();
    createWosu();
}

void InitializeSounds(){
    LoadSounds();
}

