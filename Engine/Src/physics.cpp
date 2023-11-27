
#include "../Include/physics.h"


void Physic() {


}

/***************************************************
 *  Gravity Handler Class function implementations *
 **************************************************/



void GravityHandler::Check (const Rect& r) {
    if (gravityAddicted) {
        if (onSolidGround(r)) { if (isFalling) {
                isFalling = false; onStopFalling();
            }
        }
        else
        if (!isFalling) {
         //   void PrepareSpriteGravityHandler (GridLayer* gridLayer, Sprite* sprite) {
        //        sprite->GetGravityHandler().SetOnSolidGround([gridLayer](const Rect& r){ return gridLayer->IsOnSolidGround(r); });
         //   }
            isFalling = true;
            onStartFalling();
        }
    }
}
