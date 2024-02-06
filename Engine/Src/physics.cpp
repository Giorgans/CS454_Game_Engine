
#include "../Include/physics.h"



/***************************************************
 *  Gravity Handler Class function implementations *
 **************************************************/



void GravityHandler::Check (const Rect& r) {
    if (gravityAddicted) {
        if (onSolidGround(r)) {
            if (isFalling) {
                isFalling = false;
                onStopFalling();
            }
        }
        else
        if (!isFalling) {
            isFalling = true;
            onStartFalling();
        }
    }
}


