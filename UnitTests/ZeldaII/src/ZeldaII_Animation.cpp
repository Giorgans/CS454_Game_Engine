#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/rendering.h"

extern TileLayer *terrain,*background;

/***************************************
 *  Animation Functions                *
 **************************************/

void TittleScreen_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim);
void TittleScreen_Animations_OnFinish(Animator *animator);

void Wosu_Animation_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim);

void Link_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim);
void Link_Animations_OnFinish(Animator *animator);

void Elevator_Animations_OnAction(Sprite *sprite,Animator *animator,const MovingAnimation &anim);

void InitializeAnimations(){

    auto *TitleScreenAnimation =  new FrameRangeAnimation("TitleScreen",0,AnimationFilmHolder::GetHolder().GetFilm(TitleScreen)->GetTotalFrames()-1,0,0,0,1000/3);
    auto *WalkingAnimation = new  FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);
    auto *StandingAnimation = new FrameRangeAnimation("Standing",0,0,0,0,0,FRAME_DURATION);
    auto *WosuStanding = new FrameRangeAnimation("Standing",0,0,0,0,0,FRAME_DURATION);
    auto *WosuWalking = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WosuLeft)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);
    auto *ElevatorStandingAnimation = new MovingAnimation("Standing",0,0,0,FRAME_DURATION);

    auto *TitleScreenAnimator = new FrameRangeAnimator("TitleScreenAnimator");
    auto *PlayerAnimator = new FrameRangeAnimator("PlayerAnimator");
    auto *WosuAnimator = new FrameRangeAnimator("WosuAnimator");
    std::vector<FrameRangeAnimator*> wosuAnimators;


    auto wosu=SpriteManager::GetSingleton().GetTypeList("Wosu").at(0);
    auto titles = SpriteManager::GetSingleton().GetDisplayList().at(0);
    auto Link = SpriteManager::GetSingleton().GetDisplayList().at(1);

    for(auto i : SpriteManager::GetSingleton().GetDisplayList()){
        //ELEVATOR
        if(i->GetFilm()->GetID() == Elevator && i->IsVisible()) {
            auto *ElevatorAnimator = new MovingAnimator();
            ElevatorAnimator->SetOnAction(
                    [i,ElevatorAnimator, ElevatorStandingAnimation](Animator *animator,const Animation &anim) {
                        Elevator_Animations_OnAction(i,ElevatorAnimator, *ElevatorStandingAnimation);
                    }
            );
            ElevatorAnimator->Start(StandingAnimation,GetGameTime());
        }
        //WOS
        else if (i->GetFilm()->GetID() == WosuLeft || i->GetFilm()->GetID() == WosuRight) {
            auto *wosuAnimator = new FrameRangeAnimator("WosuAnimator");
            wosuAnimator->SetOnAction(
                    [i, wosuAnimator, WosuStanding](Animator *animator, const Animation &anim) {
                        Wosu_Animation_OnAction(i, wosuAnimator, *WosuStanding);
                    }
            );
            wosuAnimator->Start(WosuStanding, GetGameTime());
            wosuAnimators.push_back(wosuAnimator);
        }
    }

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

    WosuAnimator->SetOnAction(
            [wosu,WosuAnimator, WosuWalking](Animator *animator,const Animation &anim) {
                Wosu_Animation_OnAction(wosu,WosuAnimator, *WosuWalking);
            }
    );
    TitleScreenAnimator->Start(TitleScreenAnimation,GetGameTime());

}

void Elevator_Animations_OnAction(Sprite *sprite,Animator *animator,const MovingAnimation &anim){
    auto *ElevatorStandingAnimation = new MovingAnimation("Standing",0,0,0,FRAME_DURATION);
    auto *moveDown = new MovingAnimation("Down",8,0,4,FRAME_DURATION);
    auto *moveGoingDown = new MovingAnimation("Down",28,0,4,FRAME_DURATION);

    auto* movingAnimator = (MovingAnimator*) animator;


    if(sprite->GetStateID()=="Down"){
        if(movingAnimator->GetAnim()->IsForever())
            movingAnimator->SetAnim(moveDown,GetGameTime());
        sprite->SetHasDirectMotion(true).Move(moveDown->GetDx(), moveDown->GetDy()).SetHasDirectMotion(false);

    }

    if(sprite->GetStateID()=="GoingDown"){
        if(movingAnimator->GetAnim()->IsForever())
            movingAnimator->SetAnim(moveGoingDown,GetGameTime());
        sprite->SetHasDirectMotion(true).Move(moveGoingDown->GetDx(), moveGoingDown->GetDy()).SetHasDirectMotion(false);

    }

    if(sprite->GetStateID()=="Down" && movingAnimator->GetCurrRep()==6){
        Rect terrainview ={terrain->GetViewWindow().x, terrain->GetViewWindow().y + 240 , terrain->GetViewWindow().w, terrain->GetViewWindow().h};
        terrain->SetViewWindow(terrainview);
        background->SetViewWindow(terrainview);
    }


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


SpriteVisibilityInfo isVisibleToLink(Sprite* sprite) {
    Rect Area ={terrain->GetViewWindow().x, terrain->GetViewWindow().y, terrain->GetViewWindow().w/2, terrain->GetViewWindow().h/2};
    auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
    int linkX = link->GetBox().x;
    SpriteVisibilityInfo info {false, false};

    if (sprite->IsVisible()) {
        Rect spriteBox = sprite->GetBox();
        bool isWithinDisplayArea = spriteBox.x + spriteBox.w > Area.x &&
                                   spriteBox.x < Area.x + Area.w &&
                                   spriteBox.y + spriteBox.h > Area.y &&
                                   spriteBox.y < Area.y + Area.h;

        if (isWithinDisplayArea) {
            info.isVisible = true;
            info.isRightOfLink = spriteBox.x > linkX;
        }
    }

    return info;
}

void Wosu_Animation_OnAction(Sprite *sprite, Animator *animator, const FrameRangeAnimation &anim) {

    auto *WosuWalkingLeft = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WosuLeft)->GetTotalFrames()-1,0,-2,0,FRAME_DURATION);
    auto *WosuWalkingRight = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WosuRight)->GetTotalFrames()-1,0,2,0,FRAME_DURATION);
    SpriteVisibilityInfo info = isVisibleToLink(sprite);
    auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
    auto* wosuAnimator = dynamic_cast<FrameRangeAnimator*>(animator);

    if (info.isVisible && inputs["start"]) {

        if(sprite->GetStateID()!="Active"){
            sprite->SetStateID("Active");
            if (info.isRightOfLink) {
                wosuAnimator->SetAnim(WosuWalkingLeft, GetGameTime());
                sprite->SetFilm(AnimationFilmHolder::GetHolder().Load(WosuLeft));
            } else {
                wosuAnimator->SetAnim(WosuWalkingRight, GetGameTime());
                sprite->SetFilm(AnimationFilmHolder::GetHolder().Load(WosuRight));
            }
        }

        sprite->SetFrame(wosuAnimator->GetCurrFrame());
        auto dx= wosuAnimator->GetAnim()->GetDx();
        auto dy= 4;
        terrain->GetGrid()->FilterGridMotion(sprite->GetBox(),&dx,&dy);
        sprite->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);
    }
}




void Link_Animations_OnAction(Sprite *sprite,Animator *animator,const FrameRangeAnimation &anim){
    /*** Animations ***/
    auto *StandingAnimation = new FrameRangeAnimation("Standing",0,0,0,0,0,FRAME_DURATION);
    auto *WalkingAnimation = new  FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);
    auto *AttackAnimation = new  FrameRangeAnimation("Attack",0,AnimationFilmHolder::GetHolder().GetFilm(AttackRight)->GetTotalFrames()-1,0,0,0,1000/6);
    auto *JumpAnimation = new  FrameRangeAnimation("Jump",0,AnimationFilmHolder::GetHolder().GetFilm(JumpRight)->GetTotalFrames()-1,0,0,8,1000/8);
    auto *moveDown = new FrameRangeAnimation("Down",0,0,32,0,4,FRAME_DURATION);

    /*** Questions ***/
    auto isDown = inputs["Down"] && !inputs["Right"] && !inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isMovingRight = !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isMovingLeft = !inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isStanding = !inputs["Down"] && !inputs["Right"] && !inputs["Left"] && !inputs["A"] && !inputs["S"];
    auto isDownAttack = inputs["Down"] && !inputs["Right"] && !inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isAttack = !inputs["Down"] && !inputs["Right"] && !inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isAttackRight = !inputs["Down"] && inputs["Right"] && !inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isAttackLeft = !inputs["Down"] && !inputs["Right"] && inputs["Left"] && inputs["A"] && !inputs["S"];
    auto isJump = !inputs["Down"] && !inputs["Right"] && !inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpRight = !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpLeft = !inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackUpRight = inputs["Up"] && !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackUpLeft = inputs["Up"] && !inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackDownRight = inputs["Up"] && !inputs["Down"] && inputs["Right"] && !inputs["Left"] && !inputs["A"] && inputs["S"];
    auto isJumpAttackDownLeft = !inputs["Up"] && inputs["Down"] && !inputs["Right"] && inputs["Left"] && !inputs["A"] && inputs["S"];



    Sprite * Player =  sprite;
    auto *PlayerAnimator = (FrameRangeAnimator*) animator;

    if(Player->GetStateID()=="Down" ) {
        PlayerAnimator->SetAnim(moveDown,GetGameTime());
        Player->SetHasDirectMotion(true).Move(moveDown->GetDx(), moveDown->GetDy()).SetHasDirectMotion(false);
        if(PlayerAnimator->GetCurrRep()==6){
            Player->SetHasDirectMotion(true).Move(0, 120).SetHasDirectMotion(false);
            Player->SetStateID("GoingDown");
            PlayerAnimator->SetCurrRep(0);
            PlayerAnimator->SetAnim(WalkingAnimation,GetGameTime());
        }
    }
    else if(inputs["locked"]){
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

        if (Player->GetFilm()->GetID() == JumpRight ) {
            int dx;
            if(isMovingRight)
                 dx = 4;
            else
                 dx = 0;
            int dy = -PlayerAnimator->GetAnim()->GetDy();


            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx, &dy);
            if (((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x / 2)) <= Player->GetBox().x) {
                background->Scroll(dx, 0);
                terrain->Scroll(dx, 0);
            }

            Player->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);
            Player->SetFrame(PlayerAnimator->GetCurrFrame());

            if(Player->GetFrame()==0) {
                inputs["locked"] = false;
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                PlayerAnimator->SetAnim(WalkingAnimation,GetGameTime());
                Player->SetFrame(0);
            }

        }

        if (Player->GetFilm()->GetID() == JumpLeft ) {

            int dx;
            if(isMovingLeft)
                dx = -4;
            else
                dx = 0;
            int dy = -PlayerAnimator->GetAnim()->GetDy();



            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx, &dy);

            if (((terrain->GetViewWindow().x - 4) >= 0) &&  ((terrain->GetViewWindow().x + terrain->GetViewWindow().w / 2)) > Player->GetBox().x) {
                background->Scroll(dx, 0);
                terrain->Scroll(dx, 0);
            }

            Player->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);
            Player->SetFrame(PlayerAnimator->GetCurrFrame());

            if(Player->GetFrame()==0) {
                inputs["locked"] = false;
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                PlayerAnimator->SetAnim(WalkingAnimation,GetGameTime());
                Player->SetFrame(0);
            }

        }



    }
    else{
        Player->SetStateID("");
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

            if (((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x / 2)) <= Player->GetBox().x) {
                background->Scroll(4, 0);
                terrain->Scroll(4, 0);
            }

            int dx = PlayerAnimator->GetAnim()->GetDx();
            int dy = 4;
            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx, &dy);
            Player->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);
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

            if (((terrain->GetViewWindow().x - 4) >= 0) &&  ((terrain->GetViewWindow().x + terrain->GetViewWindow().w / 2)) > Player->GetBox().x) {
                background->Scroll(-4, 0);
                terrain->Scroll(-4, 0);
            }

            int dx = -PlayerAnimator->GetAnim()->GetDx();
            int dy = 4;
            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx,&dy);
            Player->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);
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
        auto Gx = 0;
        auto Gy = 4;
        terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &Gx,&Gy);
        if(((isJump && Player->GetFilm()->GetID()==WalkingRight) || isJumpRight) && !Gy) {
            if (PlayerAnimator->GetAnim() != JumpAnimation) {
                PlayerAnimator->SetAnim(JumpAnimation, GetGameTime());
                Player->SetFrame(0);
            }
            Player->SetFilm(AnimationFilmHolder::GetHolder().Load(JumpRight));
            Player->SetFrame(0);
            inputs["locked"] = true;
        }

        if(((isJump && Player->GetFilm()->GetID()==WalkingLeft) || isJumpLeft) && !Gy) {
            if (PlayerAnimator->GetAnim() != JumpAnimation) {
                PlayerAnimator->SetAnim(JumpAnimation, GetGameTime());
                Player->SetFrame(0);
            }
            Player->SetFilm(AnimationFilmHolder::GetHolder().Load(JumpLeft));
            Player->SetFrame(0);
            inputs["locked"] = true;
        }
        if((isJumpLeft && Gy) || (isJumpRight && Gy)) {
            isStanding= true;
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

            int dx = 0;
            int dy = 4;
            terrain->GetGrid()->FilterGridMotion(Player->GetBox(), &dx, &dy);
            Player->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);


        }
    }


}

void Link_Animations_OnFinish(Animator *animator) {

}
