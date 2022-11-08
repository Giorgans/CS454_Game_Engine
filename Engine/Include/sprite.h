//
// Created by Georgios Zervos on 7/11/22.
//

#ifndef CS454_SUPER_MARIO_GAME_SPRITE_H
#define CS454_SUPER_MARIO_GAME_SPRITE_H
#include "animation.h"
#include "physics.h"

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
        MotionQuantizer& SetUsed(bool val);
        MotionQuantizer& SetRange(int h, int v) { horizMax = h, vertMax = v; used = true; return *this; }
        MotionQuantizer& SetMover(const Mover & f) { mover = f; return *this; }
        void Move (const Rect& r, int* dx, int* dy);
        MotionQuantizer () = default;
        MotionQuantizer (const MotionQuantizer&) = default;
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
    public:
        template <typename Tfunc>
        void SetMover(const Tfunc& f) { quantizer.SetMover(mover = f); }
        const Rect GetBox() const { return { x, y, frameBox.w, frameBox.h }; }
        void Move(int dx, int dy) { quantizer.Move(GetBox(), &dx, &dy); }
        void SetPos(int _x, int _y) { x = _x; y = _y; }
        void SetZorder(unsigned z) { zorder = z;}
        unsigned GetZorder() { return zorder; }
    void SetFrame(byte i) {
        if (i != frameNo) {
            assert(i < currFilm->GetTotalFrames());
            frameBox = currFilm->GetFrameBox(frameNo = i); }
    }
    byte GetFrame() const { return frameNo; }
 /*   void SetBoundingArea(const BoundingArea& area) { assert(!boundingArea); boundingArea = area.Clone(); }
    void SetBoundingArea(BoundingArea* area) {
        assert(!boundingArea);
        boundingArea = area;
    }
    auto GetBoundingArea() const -> const BoundingArea* { return boundingArea; } */
    auto GetTypeId() -> const std::string& { return typeId; }
    void SetVisibility (bool v) { isVisible = v; }
    bool IsVisible() const { return isVisible; }
    bool CollisionCheck(const Sprite* s) const;
    void Display(ALLEGRO_BITMAP *dest, const Rect& dpyArea, const Clipper& clipper) const;
    Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "")
    : x(_x), y(_y), currFilm(film), typeId (_typeId) {
            frameNo = currFilm->GetTotalFrames();
            SetFrame(0);
    }
};

template <typename Tnum> int number_sign (Tnum x) {
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

template <class T> bool clip_rect(
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

bool clip_rect (const Rect& r, const Rect& area, Rect* result) {
    return clip_rect(
            r.x,r.y,
            r.w,r.h,
            area.x,area.y,
            area.w,area.h,
            &result->x,&result->y,
            &result->w,&result->h
    );
}

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


#endif //CS454_SUPER_MARIO_GAME_SPRITE_H
