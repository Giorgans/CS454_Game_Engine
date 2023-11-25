//
// Created by Georgios Zervos on 24/11/23.
//
#include "ZeldaII.h"
#include "../../Engine/Include/sprite.h"

/***************************************
 *  Initialization Functions          *
 **************************************/


void InitializeBitmaps(){
    for(auto const f : std::__fs::filesystem::directory_iterator(AnimationBitmaps)){
        if(f.path().filename()!=".DS_Store") // hidden file on mac folder
            BitmapLoader::GetLoader().Store(f.path().filename(), al_load_bitmap( f.path().string().c_str()) );
    }
}

void InitializeFilms(){
    for(auto const f : std::__fs::filesystem::directory_iterator(AnimationBitmaps)) {
        if (f.path().filename() != ".DS_Store") { // hidden file on mac folder
            ALLEGRO_BITMAP *bitmap = BitmapLoader::GetLoader().Load(f.path().filename());
            if (bitmap == NULL)assert(false);
            int frames;
            int width;
            if(f.path().filename() == WalkingLeft || f.path().filename() == WalkingRight){
                frames = int(al_get_bitmap_width(bitmap) / 16);
                width = 16;
            }
            else {
                frames = int(al_get_bitmap_width(bitmap) / 32);
                width = 32;
            }

            std::vector<Rect> boxes = {};
            for (int i = 0; i < frames; i++)
                boxes.push_back({i * width, 0, width, 32});
            AnimationFilm *film = new AnimationFilm(bitmap, boxes, f.path().filename());

            AnimationFilmHolder::GetHolder().Store(f.path().filename(), film);

        }
    }
}


FrameRangeAnimator *PlayerAnimator = new FrameRangeAnimator("PlayerAnimator");


void InitializeAnimators(){
    auto *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);

    PlayerAnimator->Start(WalkingAnimation, GetSystemTime());

    auto link = SpriteManager::GetSingleton().GetDisplayList().at(0);
    link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
    PlayerAnimator->SetOnAction([link](Animator* animator, const Animation& anim) {} );

}



/***************************************
 *  Creating Sprites Functions        *
 **************************************/

void createLink() {
    Sprite *Link = new Sprite(LINK_STARTING_POINT_X,LINK_STARTING_POINT_Y,AnimationFilmHolder::GetHolder().Load(WalkingRight),"Link");
    Link->SetVisibility(true);
    Link->SetZorder(1);
    SpriteManager::GetSingleton().Add(Link);
}