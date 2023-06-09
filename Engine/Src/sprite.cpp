//
// Created by Georgios Zervos on 7/11/22.
//
#include "../Include/sprite.h"

SpriteManager SpriteManager::singleton;
extern TileLayer terrain;

void MotionQuantizer::Move (const Rect& r, int* dx, int* dy) {
    if (!used)
        mover(r, dx, dy);
    else
        do {
            auto sign_x = number_sign(*dx);
            auto sign_y = number_sign(*dy);
            auto dxFinal = sign_x * std::min(horizMax, sign_x * *dx);
            auto dyFinal = sign_y * std::min(vertMax, sign_y * *dy);
            mover(r, &dxFinal, &dyFinal);
            if (!dxFinal) // X motion denied
                *dx = 0;
            else
                *dx -= dxFinal;
            if (!dyFinal) // Y motion denied
                *dy = 0;
            else
                *dy -= dyFinal;
        } while (*dx || *dy);
};


bool Clipper::Clip (const Rect& r, const Rect& dpyArea, Point* dpyPos, Rect* clippedBox) const {
    Rect visibleArea;
    if (!clip_rect(r, view(), &visibleArea)) {
        clippedBox->w = clippedBox->h = 0; return false;
    }
    else {
        // clippedBox is in ‘r’ coordinates, sub-rectangle of the input rectangle
        clippedBox->x = r.x - visibleArea.x;
        clippedBox->y = r.y - visibleArea.y;

        clippedBox->w = visibleArea.w;
        clippedBox->h = visibleArea.h;

        dpyPos->x = dpyArea.x + (visibleArea.x - view().x);
        dpyPos->y = dpyArea.y + (visibleArea.y - view().y);

        return true;
    }
}

void Sprite::Display (ALLEGRO_BITMAP *dest, const Rect& dpyArea, const Clipper& clipper) const {
    Rect clippedBox;
    Point dpyPos;
    if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox)) {
        Rect clippedFrame { frameBox.x + clippedBox.x,
                            frameBox.y + clippedBox.y,
                            clippedBox.w,
                            clippedBox.h
        };
        BitmapBlitScaledSprite(currFilm->GetBitmap(),clippedFrame,dest,dpyPos);
    }
}

const Clipper MakeTileLayerClipper (TileLayer* layer) {
    return Clipper().SetView(
            [layer]() { return layer->GetViewWindow(); }
    );
}

bool clip_rect(const Rect& r, const Rect& area, Rect* result) {
    return clipping(
            r.x,r.y,
            r.w,r.h,
            area.x,area.y,
            area.w,area.h,
            &result->x,&result->y,
            &result->w,&result->h
    );
}

void GravityHandler::Check (const Rect& r) {
    if (gravityAddicted) {
        if (onSolidGround(r)) { if (isFalling) {
                isFalling = false; onStopFalling();
            }
        }
        else
        if (!isFalling) {
            isFalling = true;
            onStartFalling();
        }
    }
}

void PrepareSpriteGravityHandler (GridLayer* gridLayer, Sprite* sprite) {
    sprite->GetGravityHandler().SetOnSolidGround([gridLayer](const Rect& r){ return gridLayer->IsOnSolidGround(r); });
}

void Physic() {
    PrepareSpriteGravityHandler(terrain.GetGrid(), SpriteManager::GetSingleton().GetDisplayList().at(0));
}


void FrameRange_Action (Sprite* sprite, Animator* animator, const FrameRangeAnimation& anim) {
    auto* frameRangeAnimator = (FrameRangeAnimator*) animator;
    if (frameRangeAnimator->GetCurrFrame() != anim.GetStartFrame() || frameRangeAnimator->GetCurrRep())
        sprite->Move(anim.GetDx(), anim.GetDy());
    sprite->SetFrame(frameRangeAnimator->GetCurrFrame());
}

void createLink() {
    Sprite *Link = new Sprite(ZELDA_STARTING_POINT_X+30,ZELDA_STARTING_POINT_Y+375,AnimationFilmHolder::GetHolder().Load(WalkingRight),"Link");
    Link->SetVisibility(true);
    Link->SetZorder(1);
    SpriteManager::GetSingleton().Add(Link);
}

void InitializeSprites(){
    createLink();
}
FrameRangeAnimator *WalkingAnimator = new FrameRangeAnimator();
FrameRangeAnimator *DownAttackAnimator = new FrameRangeAnimator();

void InitializeAnimators(){
    FrameRangeAnimation *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,32,0,150);
    WalkingAnimator->Start(WalkingAnimation,GetSystemTime());
    WalkingAnimator->Progress(GetSystemTime());
    //AnimatorManager::GetManager().Register(WalkingAnimator);
    //AnimatorManager::GetManager().MarkAsRunning(WalkingAnimator);
    auto link = SpriteManager::GetSingleton().GetDisplayList().at(0);
    WalkingAnimator->SetOnAction([link](Animator* animator, const Animation& anim) {} );
    FrameRange_Action(link, WalkingAnimator, *WalkingAnimator->GetAnim());

}

void ProgAnimation(){
    /*    Sprite * Link =  SpriteManager::GetSingleton().GetDisplayList().at(0);
        if (Link->GetFilm()->GetID() == DownLeft || Link->GetFilm()->GetID() == DownRight  ) {
            if(Link->GetFilm()->GetID() == DownLeft) Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
            else Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
            WalkingAnimator->Start(WalkingAnimator->GetAnim(),GetSystemTime());
            WalkingAnimator->Progress(GetSystemTime());
        }
*/
}
