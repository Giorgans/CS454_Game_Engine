//
// Created by Georgios Zervos on 8/11/22.
//
#include "../Include/physics.h"

void GravityHandler::Check (const Rect& r) {
    if (gravityAddicted) {
        if (onSolidGround(r)) { if (isFalling) {
                isFalling = false; onStopFalling();
            } }
        else
        if (!isFalling) {
            isFalling = true;
            onStartFalling(); }
    }
}