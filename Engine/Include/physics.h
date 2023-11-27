#ifndef CS454_GAME_ENGINE_PHYSICS_H
#define CS454_GAME_ENGINE_PHYSICS_H
#include "terrain.h"

void Physic();

/*****************************************
 *  Gravity Handler Class and functions *
 ****************************************/

class GravityHandler {
public:
    using OnSolidGroundPred = std::function<bool(const Rect&)>;
    using OnStartFalling = std::function<void(void)>;
    using OnStopFalling = std::function<void(void)>;
protected:
    bool gravityAddicted = true;
    bool isFalling = false;
    OnSolidGroundPred onSolidGround;
    OnStartFalling onStartFalling;
    OnStopFalling onStopFalling;
public:
    template <typename T> void SetOnStartFalling (const T & f)
    {onStartFalling = f;}
    template <typename T> void SetOnStopFalling (const T& f)
    {onStopFalling = f;}
    template <typename T> void SetOnSolidGround (const T& f)
    {onSolidGround = f;}
    void Reset (void) { isFalling = false; }
    void Check (const Rect& r);

};

//void PrepareSpriteGravityHandler (GridLayer* gridLayer, Sprite* sprite) ;


/***************************************
 *   Motion Quantizer Class           *
 **************************************/

class MotionQuantizer {
public:
    using Mover = std::function<void(const Rect &r, int *dx, int *dy)>;
protected:
    int horizMax = 0, vertMax = 0;
    Mover mover; // filters requested motion too! bool used = false;
    bool used = false;
public:
    void SetUsed(bool val) { used = val; }
    MotionQuantizer& SetRange(int h, int v) {
        horizMax = h,vertMax = v;
        SetUsed(true);
        return *this;
    }
    MotionQuantizer& SetMover(const Mover & f) {
        mover = f;
        return *this;
    }
    void Move(const Rect& r, int* dx, int* dy);
    MotionQuantizer() = default;
    MotionQuantizer(const MotionQuantizer&) = default;
};



#endif //CS454_GAME_ENGINE_PHYSICS_H
