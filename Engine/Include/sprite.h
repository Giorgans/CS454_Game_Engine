#ifndef CS454_GAME_ENGINE_SPRITE_H
#define CS454_GAME_ENGINE_SPRITE_H
#include <vector>
#include "animation.h"
#include "physics.h"

class Clipper;

/***************************************
 *  Sprite Class                      *
 **************************************/

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
        if (directMotion) { // apply unconditionally offsets! x += dx, y += dy;
            x += dx, y += dy;
        }
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
            frameBox = currFilm->GetFrameBox(frameNo = i);
        }
    }
    Rect GetClipedBox(const Rect& dpyArea, const Clipper& clipper);

    byte GetFrame() const { return frameNo; }
    auto GetTypeId() -> const std::string& { return typeId; }
    void SetVisibility (bool v) { isVisible = v; }
    std::string GetStateID(){ return stateId;}
    void SetStateID(std::string s){stateId = s;}
    bool IsVisible() const { return isVisible; }
    bool CollisionCheck(const Sprite* s) const;
    GravityHandler& GetGravityHandler (void){ return gravity; }
    Sprite& SetHasDirectMotion (bool v) { directMotion = v; return *this; }
    bool GetHasDirectMotion (void) const { return directMotion; }
    AnimationFilm *GetFilm(){return currFilm;}
    void SetFilm(AnimationFilm *film)  {
        currFilm = film;
        frameBox = film->GetFrameBox(0);
    }
    void Display(ALLEGRO_BITMAP *dest, const Rect& dpyArea, const Clipper& clipper) const;
    Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "")
            : x(_x), y(_y), currFilm(film), typeId (_typeId) {
        frameBox = currFilm->GetFrameBox(0);
        frameNo = currFilm->GetTotalFrames();
        SetFrame(0);
    }
};

/*******************************************
 * Collision Class and signatures          *
 ******************************************/

class CollisionChecker final {
public:
    using Action = std::function<void(Sprite* s1, Sprite* s2)>;
    static CollisionChecker singleton;

protected:
    using Entry = std::tuple<Sprite*, Sprite*, Action>;
    std::list<Entry> entries;

public:
    CollisionChecker() = default;

    void Register(Sprite* s1, Sprite* s2, const Action& f);
    void Cancel(Sprite* s1, Sprite* s2);
    void Check() const;

    static CollisionChecker& GetSingleton() { return singleton; }
    static const CollisionChecker& GetSingletonConst() { return singleton; }
};

/*******************************************
 * Cliping Class and functions for Sprites *
 ******************************************/

template <class T> bool clip_rect(
        T  x,  T  y,  T  w,  T  h,
        T  wx, T  wy, T  ww, T  wh,
        T* cx, T* cy, T* cw, T* ch
) {
    *cw = T(std::min(wx + ww, x + w)) - (*cx = T(std::max(wx, x)));
    *ch = T(std::min(wy + wh, y + h)) - (*cy = T(std::max(wy, y)));
    return *cw > 0 && *ch > 0;
}

bool clip_r (const Rect& r, const Rect& area, Rect* result) ;

template <typename Tnum> int number_sign(Tnum x) {
    return x > 0 ? 1 : x < 0 ? -1 : 0;
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

const Clipper MakeTileLayerClipper (TileLayer* layer) ;


/***************************************
 *  Sprite Manager Singleton          *
 **************************************/


class SpriteManager  {
    public:
        using SpriteList = std::vector<Sprite*>;
        using TypeLists = std::map<std::string, SpriteList>;
    private:
        SpriteList dpyList;
        TypeLists types;
        static SpriteManager Manager;
    public:
        void Add (Sprite* s) {
            dpyList.push_back(s);
            auto it = types.find(s->GetTypeId());
            if (it != types.end()) {
                it->second.push_back(s);
            } else {
                types[s->GetTypeId()] = SpriteList{ s };
            }

        } //TODO: insert by ascending zorder
        void Remove (Sprite* s);
        SpriteList GetDisplayList() { return dpyList; }
        auto GetTypeList(const std::string& typeId) -> const SpriteList& { return types[typeId]; }
        static auto GetSingleton()-> SpriteManager&{ return Manager; }
        static auto GetSingletonConst() -> const SpriteManager& { return Manager; }
        SpriteManager() {};

};


#endif //CS454_GAME_ENGINE_SPRITE_H
