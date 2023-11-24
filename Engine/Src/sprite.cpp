//
// Created by Georgios Zervos on 7/11/22.
//
#include "../Include/sprite.h"

SpriteManager SpriteManager::singleton;
extern TileLayer terrain;

bool clip_r (const Rect& r, const Rect& area, Rect* result) {
    return clip_rect(
            r.x,
            r.y,
            r.w,
            r.h,
            area.x,
            area.y,
            area.w,
            area.h,
            &result->x,
            &result->y,
            &result->w,
            &result->h
    );
}

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
    if (!clip_r(r, view(), &visibleArea))
    { clippedBox->w = clippedBox->h = 0; return false; }
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
    Rect   clippedBox;
    Point  dpyPos;

    if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox)) {

        Rect clippedFrame {
                frameBox.x + clippedBox.x,
                frameBox.y + clippedBox.y,
                clippedBox.w,
                clippedBox.h
        };

        BitmapBlitScaledSprite(
                currFilm->GetBitmap(),
                clippedFrame,
                dest,
                dpyPos
        );
    }


}



const Clipper MakeTileLayerClipper (TileLayer* layer) {
    return Clipper().SetView(
            [layer](void)
            { return layer->GetViewWindow(); }
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



void InitializeSprites(){
    createLink();
}
