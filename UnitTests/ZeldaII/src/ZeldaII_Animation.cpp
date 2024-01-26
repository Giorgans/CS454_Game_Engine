#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/rendering.h"

extern std::map<std::string,bool> inputs;
extern TileLayer *terrain,*background;


/***************************************
 *  Animation Functions               *
 **************************************/

void TittleScreen_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim);
void TittleScreen_Animations_OnFinish(Animator *animator);

void Link_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim);
void Link_Animations_OnFinish(Animator *animator);

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
    if(inputs["start"]) {
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

    if (PlayerAnimator != nullptr)
        PlayerAnimator->Start(StandingAnimation, GetGameTime());
    else
        assert(true);

}


void Link_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim){
    /*** Animations ***/
    auto *StandingAnimation = new FrameRangeAnimation("Standing",0,0,0,0,0,FRAME_DURATION);
    auto *WalkingAnimation = new  FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);
    auto *AttackAnimation = new  FrameRangeAnimation("Attack",0,AnimationFilmHolder::GetHolder().GetFilm(AttackRight)->GetTotalFrames()-1,0,0,0,1000/6);
    auto *JumpAnimation = new  FrameRangeAnimation("Jump",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,2,2,FRAME_DURATION);

    /*** Questions ***/
    auto isDown = inputs["Down"] && !inputs["Right"] && !inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isMovingRight = !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isMovingLeft = !inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isStanding = !inputs["Down"] && !inputs["Right"] && !inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isDownAttack = inputs["Down"] && !inputs["Right"] && !inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isAttack = !inputs["Down"] && !inputs["Right"] && !inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isAttackRight = !inputs["Down"] && inputs["Right"] && !inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isAttackLeft = !inputs["Down"] && !inputs["Right"] && inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isJumpRight = !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpLeft = !inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackUpRight = inputs["Up"] && !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackUpLeft = inputs["Up"] && !inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackDownRight = inputs["Up"] && !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackDownLeft = !inputs["Up"] && inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && inputs["S"];


    Sprite * Player =  sprite;
    auto *PlayerAnimator = (FrameRangeAnimator*) animator;
    if(inputs["locked"]){
        if (Player->GetFilm()->GetID() == AttackRight || Player->GetFilm()->GetID() == AttackLeft){
            Player->SetFrame(PlayerAnimator->GetCurrFrame());
            if(Player->GetFrame()==AttackAnimation->GetEndFrame()) {
                inputs["locked"] = false;
                if(Player->GetFilm()->GetID() == AttackRight)
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                if(Player->GetFilm()->GetID() == AttackLeft)
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));

            }
        }

        if (Player->GetFilm()->GetID() == JumpRight || Player->GetFilm()->GetID() == JumpLeft) {

            Player->SetFrame(PlayerAnimator->GetCurrFrame());
            int dx = PlayerAnimator->GetAnim()->GetDx();
            int dy = PlayerAnimator->GetAnim()->GetDy();

            if(Player->GetFrame()<=1)
                dy = -dy;

            if(Player->GetFilm()->GetID() == JumpLeft)
                dx = -dx;

            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx, &dy);

            Player->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);

            if(Player->GetFrame()==AttackAnimation->GetEndFrame()) {
                inputs["locked"] = false;
                if(Player->GetFilm()->GetID() == JumpRight)
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                if(Player->GetFilm()->GetID() == JumpLeft)
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));

            }

        }


    }
    else{
        if (isDown) {
            PlayerAnimator->SetAnim(StandingAnimation, GetGameTime());
            if (Player->GetFilm()->GetID() == WalkingLeft)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));

            if (Player->GetFilm()->GetID() == WalkingRight)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));

            Player->SetFrame(0);
        }

        if (isDownAttack) {
            PlayerAnimator->SetAnim(StandingAnimation, GetGameTime());
            if (Player->GetFilm()->GetID() == WalkingLeft)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));

            if (Player->GetFilm()->GetID() == WalkingRight)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));

            Player->SetFrame(1);
        }

        if (isMovingRight) {

            if (Player->GetFilm()->GetID() != WalkingRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                Player->SetFrame(0);
            }
            if (PlayerAnimator->GetAnim() != WalkingAnimation) {
                PlayerAnimator->SetAnim(WalkingAnimation, GetGameTime());
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
            }

            if (((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x / 2)) <=
                Player->GetBox().x) {
                background->Scroll(4, 0);
                terrain->Scroll(4, 0);
            }

            int dx = PlayerAnimator->GetAnim()->GetDx();
            int dy = 0;
            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx, &dy);
            Player->SetHasDirectMotion(true).Move(dx, 0).SetHasDirectMotion(false);
            Player->SetFrame(PlayerAnimator->GetCurrFrame());
        }

        if (isMovingLeft) {
            if (Player->GetFilm()->GetID() != WalkingLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                Player->SetFrame(0);
            }
            if (PlayerAnimator->GetAnim() != WalkingAnimation) {
                PlayerAnimator->SetAnim(WalkingAnimation, GetGameTime());
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
            }

            if (((terrain->GetViewWindow().x - 4) >= 0) &&
                ((terrain->GetViewWindow().x + terrain->GetViewWindow().w / 2)) <= Player->GetBox().x) {
                background->Scroll(-4, 0);
                terrain->Scroll(-4, 0);
            }

            int dx = -PlayerAnimator->GetAnim()->GetDx();
            int dy = 0;
            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx,&dy);
            Player->SetHasDirectMotion(true).Move(dx, 0).SetHasDirectMotion(false);
            Player->SetFrame(PlayerAnimator->GetCurrFrame());
        }


        if (isAttack) {
            if (PlayerAnimator->GetAnim() != AttackAnimation) {
                PlayerAnimator->SetAnim(AttackAnimation, GetGameTime());
                Player->SetFrame(0);
            }

            if (Player->GetFilm()->GetID() == WalkingLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackLeft));
                Player->SetFrame(0);
            }

            if (Player->GetFilm()->GetID() == WalkingRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackRight));
                Player->SetFrame(0);
            }
            inputs["locked"] = true;
        }

        if (isAttackRight) {
            if (PlayerAnimator->GetAnim() != AttackAnimation) {
                PlayerAnimator->SetAnim(AttackAnimation, GetGameTime());
                Player->SetFrame(0);
            }

            Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackRight));
            Player->SetFrame(0);
            inputs["locked"] = true;
        }

        if (isAttackLeft) {
            if (PlayerAnimator->GetAnim() != AttackAnimation) {
                PlayerAnimator->SetAnim(AttackAnimation, GetGameTime());
                Player->SetFrame(0);
            }

            Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackLeft));
            Player->SetFrame(0);
            inputs["locked"] = true;
        }

        if(isJumpRight) {
            if (PlayerAnimator->GetAnim() != JumpAnimation) {
                PlayerAnimator->SetAnim(JumpAnimation, GetGameTime());
                Player->SetFrame(0);
            }
            Player->SetFilm(AnimationFilmHolder::GetHolder().Load(JumpRight));
            Player->SetFrame(0);
            inputs["locked"] = true;
        }

        if(isJumpLeft) {
            if (PlayerAnimator->GetAnim() != JumpAnimation) {
                PlayerAnimator->SetAnim(JumpAnimation, GetGameTime());
                Player->SetFrame(0);
            }
            Player->SetFilm(AnimationFilmHolder::GetHolder().Load(JumpLeft));
            Player->SetFrame(0);
            inputs["locked"] = true;
        }



        if (isStanding) {
            if (PlayerAnimator->GetAnim() != StandingAnimation) {
                PlayerAnimator->SetAnim(StandingAnimation, GetGameTime());
                Player->SetFrame(0);
            }
            if (Player->GetFilm()->GetID() == DownLeft || Player->GetFilm()->GetID() == AttackLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                Player->SetFrame(0);
            }
            if (Player->GetFilm()->GetID() == DownRight || Player->GetFilm()->GetID() == AttackRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                Player->SetFrame(0);
            }

        }
    }


}

void Link_Animations_OnFinish(Animator *animator) {

}
