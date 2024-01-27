#ifndef CS454_GAME_ENGINE_PHYSICS_H
#define CS454_GAME_ENGINE_PHYSICS_H
#include "terrain.h"


/*****************************************
 *  Gravity Handler Class and functions *
 ****************************************/

class GravityHandler {
    public:
        using OnSolidGroundPred 	= std::function<bool(const Rect&)>;
        using OnStartFalling	= std::function<void(void)>;
        using OnStopFalling	= std::function<void(void)>;
    protected:
        bool		isFalling = false; // state variable
        OnSolidGroundPred	onSolidGround;
        OnStartFalling	onStartFalling;
        OnStopFalling	onStopFalling;
    public:
    bool		gravityAddicted = false; // config variable
    void SetOnStartFalling (const OnStartFalling& f)
        { onStartFalling = f; }
        void SetOnStopFalling (const OnStopFalling& f)
        { onStopFalling = f; }
        void SetOnSolidGround (const OnSolidGroundPred& f)
        { onSolidGround = f; }
        void		Reset (void) { isFalling = false; }
        void		Check (const Rect& r);
};



/***************************************
 *   Motion Quantizer Class           *
 **************************************/



class MotionQuantizer {
public:
    using Mover = std::function<void(const Rect& r, int* dx, int* dy)>;
protected:
    int	horizMax = 0, vertMax = 0;
    Mover	mover; // filters requested motion too!
    bool	used = false;
public:
    MotionQuantizer&	SetUsed (bool val);
    MotionQuantizer&	SetRange (int h, int v)
    { horizMax = h, vertMax = v; used = true; return *this; }
    MotionQuantizer&	SetMover (const Mover & f){ mover = f; return *this; }
    void		Move (const Rect& r, int* dx, int* dy);
    MotionQuantizer (void) = default;
    MotionQuantizer (const MotionQuantizer&) = default;
};


#endif //CS454_GAME_ENGINE_PHYSICS_H
