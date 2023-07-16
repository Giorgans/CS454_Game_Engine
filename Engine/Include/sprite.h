//
// Created by Georgios Zervos on 7/11/22.
//

#ifndef CS454_SUPER_MARIO_GAME_SPRITE_H
#define CS454_SUPER_MARIO_GAME_SPRITE_H
#include <vector>
#include "animation.h"

void Physic();
void ProgAnimation();

#define PLAYER_TYPE "player"
#define ENEMY_TYPE "enemy"

class Clipper;

// generic quantizer, can be used to filter motion with any terrain
// motion filtering function

class MotionQuantizer {
    public:
        using Mover = std::function<void(const Rect &r, int *dx, int *dy)>;
    protected:
        int horizMax = 0, vertMax = 0;
        Mover mover; // filters requested motion too! bool used = false;
        bool used = false;
    public:
        MotionQuantizer& SetUsed(bool val) { used = val; }
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

class Sprite {
    public:
        using Mover = std::function<void(const Rect&, int* dx, int* dy)>;
    protected:
        byte frameNo = 0;
        Rect frameBox; // inside the film
        int x = 0, y = 0;
        bool isVisible = false;
        AnimationFilm* currFilm = nullptr;
        //BoundingArea* boundingArea = nullptr;
        unsigned zorder = 0;
        std::string typeId, stateId;
        Mover mover;
        MotionQuantizer quantizer;
        bool directMotion = false;
        GravityHandler gravity;
    public:
        template <typename Tfunc>
        void SetMover(const Tfunc& f) { quantizer.SetMover(mover = f); }
        Rect GetBox() const { return { x, y, frameBox.w, frameBox.h }; }
        Sprite& Move (int dx, int dy) {
            if (directMotion) // apply unconditionally offsets! x += dx, y += dy;
                x += dx, y += dy;
            else {
                quantizer.Move(GetBox(), &dx, &dy);
                gravity.Check(GetBox());
            }
            return *this;
        }
        void SetPos(int _x, int _y) { x = _x; y = _y; }
        void SetZorder(unsigned z) { zorder = z;}
        unsigned GetZorder() { return zorder; }
    void SetFrame(byte i) {
            if (i != frameNo) {
                assert(i < currFilm->GetTotalFrames());
                frameBox = currFilm->GetFrameBox(frameNo = i); }
    }
    byte GetFrame() const { return frameNo; }
    auto GetTypeId() -> const std::string& { return typeId; }
    void SetVisibility (bool v) { isVisible = v; }
    bool IsVisible() const { return isVisible; }
    bool CollisionCheck(const Sprite* s) const;
    GravityHandler& GetGravityHandler (void){ return gravity; }
    Sprite& SetHasDirectMotion (bool v) { directMotion = true; return *this; }
    bool GetHasDirectMotion (void) const { return directMotion; }
    AnimationFilm *GetFilm(){return currFilm;}
    void SetFilm(AnimationFilm *film)  {
        currFilm = film;
        frameBox = film->GetFrameBox(0);
    }
    void Display(ALLEGRO_BITMAP *dest, const Rect& dpyArea, const Clipper& clipper) const;
    Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "")
    : x(_x), y(_y), currFilm(film), typeId (_typeId) {
            frameNo = currFilm->GetTotalFrames();
            SetFrame(0);
    }
};

class SpriteManager  {
    public:
        using SpriteList = std::vector<Sprite*>;
        using TypeLists = std::map<std::string, SpriteList>;
    private:
        SpriteList dpyList;
        TypeLists types;
        static SpriteManager singleton;
    public:
        void Add (Sprite* s) {
            dpyList.push_back(s);
        } //TODO: insert by ascending zorder
        void Remove (Sprite* s);
        SpriteList GetDisplayList() { return dpyList; }
        auto GetTypeList(const std::string& typeId) -> const SpriteList& { return types[typeId]; }
        static auto GetSingleton()-> SpriteManager&{ return singleton; }
        static auto GetSingletonConst() -> const SpriteManager& { return singleton; }
        SpriteManager() {};

};

template <typename Tnum> int number_sign(Tnum x) {
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

template <class T> bool clipping(
        T x, T y,
        T w, T h,
        T wx,T wy,
        T ww,T wh,
        T* cx, T* cy
        ,T* cw,T* ch
){
    *cw = T(std::min(wx + ww, x + w)) - (*cx = T(std::max(wx, x)));
    *ch = T(std::min(wy + wh, y + h)) - (*cy = T(std::max(wy, y)));
    return *cw > 0 && *ch > 0;
}

bool clip_rect(const Rect& r, const Rect& area, Rect* result);
// generic clipper assuming any terrain-based view // and any bitmap-based display area
class Clipper {
    public:
        using View = std::function<const Rect&(void)>;
    private:
        View view;
    public:
        Clipper& SetView(const View & f) { view = f; return *this; }
        bool Clip (
                const Rect& r,
                const Rect& dpyArea,
                Point* dpyPos,
                Rect* clippedBox
        ) const;
        Clipper() = default;
        Clipper(const Clipper&) = default;
};
const Clipper MakeTileLayerClipper (TileLayer* layer) ;
void PrepareSpriteGravityHandler (GridLayer* gridLayer, Sprite* sprite) ;
void FrameRange_Action (Sprite* sprite, Animator* animator, const FrameRangeAnimation& anim) ;
void InitializeSprites();


#endif //CS454_SUPER_MARIO_GAME_SPRITE_H
