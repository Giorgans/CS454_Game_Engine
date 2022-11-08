//
// Created by Georgios Zervos on 8/11/22.
//

#ifndef CS454_SUPER_MARIO_GAME_PHYSICS_H
#define CS454_SUPER_MARIO_GAME_PHYSICS_H
#include "terrain.h"
class GravityHandler {
    public:
        using OnSolidGroundPred = std::function<bool(const Rect&)>;
        using OnStartFalling = std::function<void(void)>;
        using OnStopFalling = std::function<void(void)>;
    protected:
        bool gravityAddicted = false;
        bool isFalling = false;
        OnSolidGroundPred onSolidGround;
        OnStartFalling onStartFalling;
        OnStopFalling onStopFalling;
    public:
        template <typename T> void SetOnStartFalling (const OnStartFalling f) { onStartFalling = f; }
        template <typename T> void SetOnStopFalling (const T& f) { onStopFalling = f; }
        template <typename T> void SetOnSolidGround (const T& f) { onSolidGround = f; }
        void Reset() { isFalling = false; }
        void Check(const Rect& r);
};

#endif //CS454_SUPER_MARIO_GAME_PHYSICS_H
