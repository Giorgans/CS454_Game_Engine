#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/rendering.h"

extern uint64_t GameTime;
extern std::map<std::string,bool> inputs;
extern TileLayer *terrain,*background;


/***************************************
 *  Animation Functions               *
 **************************************/

void TittleScreen_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim);
void TittleScreen_Animations_OnFinish(Animator *animator);

void Link_Animations_OnStart(Animator *animator);
void Link_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim);
void Link_Animations_OnFinish(Animator *animator);

void ZeldaII_Animations(){
    AnimatorManager manager = AnimatorManager::GetManager();
    manager.Progress(GameTime);

}

void InitializeAnimations(){

    auto *TitleScreenAnimation =  new FrameRangeAnimation("TitleScreen",0,AnimationFilmHolder::GetHolder().GetFilm(TitleScreen)->GetTotalFrames()-1,0,0,0,1000/3);
    auto *WalkingAnimation = new  FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);
    auto *StandingAnimation = new FrameRangeAnimation("Standing",0,0,0,0,0,FRAME_DURATION);

    auto *TitleScreenAnimator = new FrameRangeAnimator("TitleScreenAnimator");
    auto *PlayerAnimator = new FrameRangeAnimator("PlayerAnimator");

    auto titles = SpriteManager::GetSingleton().GetDisplayList().at(0);
    auto Link = SpriteManager::GetSingleton().GetDisplayList().at(1);

    TitleScreenAnimator->SetOnAction(
            [titles,TitleScreenAnimator, TitleScreenAnimation](Animator *animator,const Animation &anim) {
                TittleScreen_Animations_OnAction(titles,TitleScreenAnimator, *TitleScreenAnimation);
            }
    );

    TitleScreenAnimator->SetOnFinish([PlayerAnimator](Animator *animator) {TittleScreen_Animations_OnFinish(PlayerAnimator);});


    PlayerAnimator->SetOnAction(
            [Link,PlayerAnimator, WalkingAnimation](Animator *animator,const Animation &anim) {
                Link_Animations_OnAction(Link,PlayerAnimator, *WalkingAnimation);
            }
    );

    PlayerAnimator->SetOnFinish([PlayerAnimator](Animator *animator) {Link_Animations_OnFinish(PlayerAnimator);});




    TitleScreenAnimator->Start(TitleScreenAnimation,GetGameTime());

}

void TittleScreen_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim){
    auto* frameRangeAnimator = (FrameRangeAnimator*) animator;
    sprite->SetFrame(frameRangeAnimator->GetCurrFrame());
    if(inputs.at("start")) {
        auto titlescr = SpriteManager::GetSingleton().GetDisplayList().at(0);
        titlescr->SetVisibility(false);
        auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
        link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
        link->SetVisibility(true);
        frameRangeAnimator->Stop();
    }
}

void TittleScreen_Animations_OnFinish(Animator *animator){
    auto *StandingAnimation = new FrameRangeAnimation("Standing",0,0,0,0,0,FRAME_DURATION);

    auto *PlayerAnimator = (FrameRangeAnimator*) animator;

    if (PlayerAnimator != nullptr) {
        PlayerAnimator->Start(StandingAnimation, GetGameTime());
    } else {
        assert(true);
    }
}


void Link_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim){
    /*** Animations ***/
    auto *StandingAnimation = new FrameRangeAnimation("Standing",0,0,0,0,0,FRAME_DURATION);
    auto *WalkingAnimation = new  FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);

    /*** Questions ***/
    auto isMovingDown = inputs["Down"] && !inputs["Right"] && !inputs["Left"];
    auto isMovingRight = !inputs["Down"] && inputs["Right"] && !inputs["Left"];
    auto isMovingLeft = !inputs["Down"] && !inputs["Right"] && inputs["Left"];
    auto isStanding = !inputs["Down"] && !inputs["Right"] && !inputs["Left"];

    Sprite * Player =  sprite;
    auto *PlayerAnimator = (FrameRangeAnimator*) animator;

        if (isMovingDown) {
            PlayerAnimator->SetAnim(StandingAnimation,GetGameTime());
            if (Player->GetFilm()->GetID() == WalkingLeft)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));

            if (Player->GetFilm()->GetID() == WalkingRight)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));

            Player->SetFrame(0);
        }
         if (inputs["Down"] && inputs["A"])
            Player->SetFrame(1);

         if (isMovingRight) {

            if (Player->GetFilm()->GetID() != WalkingRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                Player->SetFrame(0);
            }
             if(PlayerAnimator->GetAnim() != WalkingAnimation) {
                 PlayerAnimator->SetAnim(WalkingAnimation, GetGameTime());
                 Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
             }

            if (((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x / 2)) <=
                Player->GetBox().x) {
                background->Scroll(4, 0);
                terrain->Scroll(4, 0);
            }

            int dx = PlayerAnimator->GetAnim()->GetDx();
            terrain->GetGrid()->FilterGridMotionRight(Player->GetBox(), &dx);
            Player->SetHasDirectMotion(true).Move(dx, 0).SetHasDirectMotion(false);
            Player->SetFrame(PlayerAnimator->GetCurrFrame());
        }

         if (isMovingLeft) {
            if (Player->GetFilm()->GetID() != WalkingLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                Player->SetFrame(0);
            }
             if(PlayerAnimator->GetAnim() != WalkingAnimation) {
                 PlayerAnimator->SetAnim(WalkingAnimation, GetGameTime());
                 Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
             }

            if (((terrain->GetViewWindow().x - 4) >= 0) &&
                ((terrain->GetViewWindow().x + terrain->GetViewWindow().w / 2)) <= Player->GetBox().x) {
                background->Scroll(-4, 0);
                terrain->Scroll(-4, 0);
            }

            int dx = -PlayerAnimator->GetAnim()->GetDx();
            terrain->GetGrid()->FilterGridMotionLeft(Player->GetBox(), &dx);
            Player->SetHasDirectMotion(true).Move(dx, 0).SetHasDirectMotion(false);
            Player->SetFrame(PlayerAnimator->GetCurrFrame());
        }

         if(isStanding) {
             if(PlayerAnimator->GetAnim() != StandingAnimation) {
                 PlayerAnimator->SetAnim(StandingAnimation, GetGameTime());
                 Player->SetFrame(0);
             }
             if (Player->GetFilm()->GetID() == DownLeft) {
                 Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                 Player->SetFrame(0);
             }
             if (Player->GetFilm()->GetID() == DownRight) {
                 Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                 Player->SetFrame(0);
             }

         }




}

void Link_Animations_OnFinish(Animator *animator) {

}
