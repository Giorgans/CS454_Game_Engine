#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/rendering.h"

extern FrameRangeAnimator *PlayerAnimator,*TitleScreenAnimator;
extern uint64_t currT;
extern TileLayer *terrain,*background;

/***************************************
 *  Main Loop Animation Function      *
 **************************************/

void ZeldaII_Animations(){
    if(!inputs.at("start")) {
        TitleScreenAnimations();
    }
    else {
        Link_Animations();
    }
}


/***************************************
 *  Animation Functions               *
 **************************************/

void TitleScreenAnimations(){
    TitleScreenAnimator->Progress(currT);
}

void Link_Animations(){

    Sprite * Player =  SpriteManager::GetSingleton().GetDisplayList().at(0);
    auto *AttackRightAnimation = new FrameRangeAnimation("AttackRight",0,AnimationFilmHolder::GetHolder().GetFilm(AttackRight)->GetTotalFrames()-1,0,0,0,1000/3);
    auto *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,1000/10);

    if(inputs.at("locked")){
        if(Player->GetFilm()->GetID() == AttackRight || Player->GetFilm()->GetID() == AttackLeft ){
            PlayerAnimator->Progress(currT);
            Player->SetFrame(PlayerAnimator->GetCurrFrame());
            if(PlayerAnimator->GetCurrFrame() == PlayerAnimator->GetAnim()->GetEndFrame())
                inputs.at("locked") = false;

            if(!inputs.at("locked")){
                inputs.at("A") = false;
                if (Player->GetFilm()->GetID() == AttackRight) {
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));

                } else if (Player->GetFilm()->GetID() == AttackLeft) {
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                }

                PlayerAnimator->Start(WalkingAnimation, currT);
                FrameRange_Action(Player, PlayerAnimator, *PlayerAnimator->GetAnim());
            }
        }
    }
    else {
        if (inputs.at("Down")) {
            PlayerAnimator->Stop();
            if (Player->GetFilm()->GetID() == WalkingLeft)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));

            if (Player->GetFilm()->GetID() == WalkingRight)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));

            Player->SetFrame(0);
        } else {
            if (Player->GetFilm()->GetID() == DownLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                Player->SetFrame(0);
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), currT);
                PlayerAnimator->Progress(currT);
            }
            if (Player->GetFilm()->GetID() == DownRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                Player->SetFrame(0);
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), currT);
                PlayerAnimator->Progress(currT);
            }
        }

        if (inputs.at("Down") && inputs.at("A"))
            Player->SetFrame(1);


        if (inputs.at("Right") && !inputs.at("Down")) {
            if (Player->GetFilm()->GetID() == WalkingRight)
                PlayerAnimator->Progress(currT);
            else if (Player->GetFilm()->GetID() == WalkingLeft || Player->GetFilm()->GetID() == DownLeft ||
                     Player->GetFilm()->GetID() == DownRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), currT);
                PlayerAnimator->Progress(currT);
            }
            if (((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x / 2)) <=
                Player->GetBox().x) {
                background->Scroll(4, 0);
                terrain->Scroll(4, 0);
            }
            int dx = PlayerAnimator->GetAnim()->GetDx();

            terrain->GetGrid()->FilterGridMotionRight(Player->GetBox(), &dx);
            Player->SetHasDirectMotion(true).Move(dx, 0);

            Player->SetFrame(PlayerAnimator->GetCurrFrame());

        }

        if (inputs.at("Left") && !inputs.at("Down")) {
            if (Player->GetFilm()->GetID() == WalkingLeft) {
                PlayerAnimator->Progress(currT);
            }
            if (Player->GetFilm()->GetID() == WalkingRight || Player->GetFilm()->GetID() == DownLeft ||
                Player->GetFilm()->GetID() == DownRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), currT);
                PlayerAnimator->Progress(currT);
            }
            if (((terrain->GetViewWindow().x - 4) >= 0) &&
                ((terrain->GetViewWindow().x + terrain->GetViewWindow().w / 2)) <= Player->GetBox().x) {
                background->Scroll(-4, 0);
                terrain->Scroll(-4, 0);
            }

            int dx = -PlayerAnimator->GetAnim()->GetDx();

            terrain->GetGrid()->FilterGridMotionLeft(Player->GetBox(), &dx);
            Player->SetHasDirectMotion(true).Move(dx, 0);

            Player->SetFrame(PlayerAnimator->GetCurrFrame());

        }

        if (inputs.at("A") && !inputs.at("Down")) {
            PlayerAnimator->Stop();

            inputs.at("locked")= true;
            if (Player->GetFilm()->GetID() == WalkingRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackRight));

            } else if (Player->GetFilm()->GetID() == WalkingLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackLeft));
            }
            inputs.at("A") = false;
            PlayerAnimator->Start(AttackRightAnimation, currT);
            PlayerAnimator->Progress(currT);
            Player->SetFrame(0);

        }
    }
}


