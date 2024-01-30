#include "../Include/sprite.h"
#include "../Include/rendering.h"

SpriteManager SpriteManager::Manager;
extern TileLayer *terrain;

/*******************************************
 * Sprite Class Function Implementations  *
 ******************************************/

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

void SpriteManager::CleanUp(){
    dpyList.clear();
    for (auto& instance : types) {
        instance.second.clear();
    }
}


/*******************************************
 * Collision functions                     *
 ******************************************/

CollisionChecker CollisionChecker::singleton;

void CollisionChecker::Register(Sprite* s1, Sprite* s2, const Action& f) {
    entries.emplace_back(s1, s2, f);
}

void CollisionChecker::Cancel(Sprite* s1, Sprite* s2) {
    auto it = std::find_if(entries.begin(), entries.end(),
                           [s1, s2](const Entry& e) {
                               return (std::get<0>(e) == s1 && std::get<1>(e) == s2) ||
                                      (std::get<0>(e) == s2 && std::get<1>(e) == s1);
                           }
    );
    if (it != entries.end()) {
        entries.erase(it);
    }
}

void CollisionChecker::Check() const {
    for (const auto& e : entries) {
        Sprite* s1 = std::get<0>(e);
        Sprite* s2 = std::get<1>(e);
        Action action = std::get<2>(e);

        if (s1->CollisionCheck(s2)) {
            action(s1, s2);
        }
    }
}

bool Sprite::CollisionCheck(const Sprite* other) const {
    // Example of a simple bounding box collision detection
    Rect thisBox = this->GetBox(); // Assuming GetBox() returns the bounding box of the sprite
    Rect otherBox = other->GetBox();

    bool collisionX = thisBox.x + thisBox.w >= otherBox.x &&
                      otherBox.x + otherBox.w >= thisBox.x;
    bool collisionY = thisBox.y + thisBox.h >= otherBox.y &&
                      otherBox.y + otherBox.h >= thisBox.y;

    return collisionX && collisionY;
}


/*******************************************
 * Cliping  functions for Sprites         *
 ******************************************/

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

const Clipper MakeTileLayerClipper (TileLayer* layer) {
    return Clipper().SetView(
            [layer](void)
            { return layer->GetViewWindow(); }
    );
}


/*******************************************
 * Motion functions for Sprites         *
 ******************************************/


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

