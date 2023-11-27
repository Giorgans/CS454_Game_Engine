#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/rendering.h"
#include <filesystem>
extern FrameRangeAnimator *PlayerAnimator;
extern uint64_t currT;
extern std::map<std::string,bool> inputs;



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
            else if(f.path().filename() == WalkingLeft || f.path().filename() == WalkingRight){
                frames = int(al_get_bitmap_width(bitmap) / 16);
                width = 16;
                height = 32;
            }
            else {
                frames = int(al_get_bitmap_width(bitmap) / 32);
                width = 32;
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

FrameRangeAnimator *PlayerAnimator = new FrameRangeAnimator("PlayerAnimator");
FrameRangeAnimator *TitleScreenAnimator = new FrameRangeAnimator("TitleScreenAnimator");

void InitializeAnimators(){
    auto *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);
    auto *TitleScreenAnimation = new FrameRangeAnimation("TitleScreen",0,AnimationFilmHolder::GetHolder().GetFilm(TitleScreen)->GetTotalFrames()-1,0,0,0,1000/3);
    TitleScreenAnimator->Start(TitleScreenAnimation,currT);


    PlayerAnimator->Start(WalkingAnimation, GetSystemTime());

    auto link = SpriteManager::GetSingleton().GetDisplayList().at(0);
    link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
    PlayerAnimator->SetOnAction([link](Animator* animator, const Animation& anim) {} );

}

void InitializeSprites(){
    createLink();
}

