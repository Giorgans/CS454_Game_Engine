//
// Created by Georgios Zervos on 6/11/22.
//

#ifndef CS454_SUPER_MARIO_GAME_ANIMATION_H
#define CS454_SUPER_MARIO_GAME_ANIMATION_H
#include <vector>
#include <list>
#include <map>
#include <set>
#include "terrain.h"
#include <filesystem>
#include "timing.h"
#include "sound.h"
#include "../paths.h"
#define WalkingRight "link.right.png"
#define WalkingLeft "link.left.png"
#define DownLeft "link.DownAttack.left.png"
#define DownRight "link.DownAttack.right.png"
#define AttackLeft "link.attack.left.png"
#define AttackRight "link.attack.right.png"

void setgametime();

void Animations();

class AnimationFilm {
    private:
        std::vector<Rect> boxes;
        ALLEGRO_BITMAP *bitmap;
        std::string id;
    public:
        auto GetBoxes() const { return boxes; }
        int GetTotalFrames() const { return boxes.size(); }
        ALLEGRO_BITMAP *GetBitmap(){ return bitmap; }
        auto GetID ()  { return id; }
        const Rect& GetFrameBox (byte frameNo) const { assert(boxes.size()>frameNo); return boxes[frameNo]; }
        void DisplayFrame (ALLEGRO_BITMAP *dest, const Point& at, byte frameNo) const
            {BitmapBlit(bitmap,GetFrameBox(frameNo),dest,at);}
        void SetBitmap (ALLEGRO_BITMAP *b) { assert(!bitmap); this->bitmap = b; }
        void Append (const Rect& r) { boxes.push_back(r); }
        AnimationFilm (const std::string& _id) : id (_id){}
        AnimationFilm (ALLEGRO_BITMAP *bitmap, const std::vector<Rect>& boxes, const std::string& id) {
            this->bitmap = bitmap;
            this->boxes = boxes;
            this->id = id;
        };
};

/**
 * Loads the bitmaps to the Animation Film Holder
 */
class BitmapLoader  {
    private:
        using Bitmaps = std::map<std::string,ALLEGRO_BITMAP*>;
        ALLEGRO_BITMAP *GetBitmap(const std::string &path) const {
            return  bitmaps.find(path)->second != bitmaps.end()->second ? bitmaps.find(path)->second : nullptr ;
        }
        static BitmapLoader Loader; // singleton
    public:
    Bitmaps bitmaps;

    static auto GetLoader() -> BitmapLoader& { return Loader; }
        void Store(const std::string& filename,ALLEGRO_BITMAP *bitmap){
            bitmaps[filename] = bitmap;
        }
        ALLEGRO_BITMAP *Load (const std::string& filename) {
            if(bitmaps.count(filename))
                return bitmaps.at(filename);
            else return NULL;
        }
        void CleanUp () {
            for (auto &i: bitmaps) al_destroy_bitmap(i.second);
            bitmaps.clear();
        }
        BitmapLoader () {}
        ~BitmapLoader() { CleanUp(); }
};

/**
 * Holds all the Animation Films
 */
class AnimationFilmHolder {
    public:
        using Parser = std::function<bool (std::list<AnimationFilm>& output, const std::string& input)>;
        using EntryParser = std::function<
                int (// -1=error, 0=ended gracefully, else #chars read
                        int startPos,
                        const std::string& input,
                        std::string& idOutput,
                        std::string& pathOutput,
                        std::vector<Rect>& rectsOutput
                )>;
    private:
        using Films = std::map<std::string, AnimationFilm*>;
        Films films;
        static AnimationFilmHolder holder; // singleton
    public:
        static auto GetHolder() -> AnimationFilmHolder& { return holder; }
        //void Load (const std::string& text, const EntryParser& entryParser);
        //void Load (const std::string& text, const Parser& parser);
        AnimationFilm *Load(const std::string& text){
            return films[text];
        }
        void Store(const std::string& filename,AnimationFilm *film){
            films[filename] = film;
        }
        void CleanUp ();
        auto GetFilm (const std::string& id) -> const AnimationFilm* const;

        AnimationFilmHolder () {}
        ~AnimationFilmHolder() { CleanUp(); }
};

/***************************
 * Animation Categories
 ***************************/

class Animation  {
    protected:
        std::string id;
    public:
        const std::string& GetId() { return id; }
        void SetId ( const std::string& _id);
        virtual Animation* Clone() const = 0;
        Animation (const std::string& _id) : id(_id){}
        virtual ~Animation(){}
};

/**
 * Moving animation class : basic moving / displacement
 */
class MovingAnimation : public Animation {
    protected:
        unsigned reps = 1; // 0=forever
        int dx = 0, dy = 0;
        uint64_t delay = 0;
    public:
        using Me = MovingAnimation;
        int GetDx() const { return dx; }
        Me& SetDx(int v) { dx = v; return *this; }
        int GetDy() const { return dy; }
        Me& SetDy(int v) { dy = v; return *this; }
        unsigned GetDelay() const  { return delay; }
        Me& SetDelay(unsigned v) { delay = v; return *this; }
        unsigned GetReps() const { return reps; }
        Me& SetReps(unsigned n) { reps = n; return *this; }
        bool IsForever() const  { return !reps; }
        Me& SetForever() { reps = 0; return *this; }
        Animation* Clone() const override {
            return new MovingAnimation(id, reps, dx, dy, delay);
        }
        MovingAnimation(const std::string& _id, unsigned _reps, int _dx, int _dy, unsigned _delay
        ): Animation(_id), reps (_reps), dx(_dx), dy(_dy), delay(_delay) {}
};

/**
 * Frame Range : sequence
 */
class FrameRangeAnimation : public MovingAnimation {
    protected:
        unsigned start = 0, end = 0;
    public:
        using Me = FrameRangeAnimation;
        unsigned GetStartFrame () const { return start; }
        Me& SetStartFrame (unsigned v) { start = v; return *this; }
        unsigned GetEndFrame () const { return end; }
        Me& SetEndFrame (unsigned v) { end = v; return *this; }
        Animation* Clone() const override {
            return new FrameRangeAnimation(id, start, end, GetReps(), GetDx(), GetDy(), GetDelay());
        }
        FrameRangeAnimation (
            const std::string _id,
            unsigned s, unsigned e,
            unsigned r, int dx, int dy, int d
            ): start(s), end(e), MovingAnimation(id, r, dx, dy, d){}
};

/**
 * Frame List: montage
 */
class FrameListAnimation : public MovingAnimation {
    public:
        using Frames = std::vector<unsigned>;
    protected:
        Frames frames;
    public:
        const Frames & GetFrames () const { return frames;}
        void SetFrames (const Frames& f) { frames = f; }
        Animation* Clone() const override {
            return new FrameListAnimation(id,GetFrames(), GetReps(), GetDx(), GetDy(), GetDelay());
        }
        FrameListAnimation(
            const std::string& _id,
            Frames _frames,
            unsigned r, int dx, int dy, unsigned d
        ): frames(_frames), MovingAnimation(id, r, dx, dy, d){}
};

struct PathEntry {
    int dx = 0, dy = 0;
    unsigned frame = 0;
    PathEntry() = default;
    PathEntry(const PathEntry&) = default;
};

/**
 * Combo of different moves
 */
class MovingPathAnimation : public Animation {
    public:
        using Path = std::vector<PathEntry>;
    private:
        Path path;
    public:
        const Path &GetPath(void) const { return path; }
        void SetPath(const Path &p) { path = p; }
        Animation *Clone(void) const override {
            return new MovingPathAnimation(id, path);
        }
        MovingPathAnimation(
                const std::string &_id,
                const Path &_path
                ) : path(_path), Animation(id) {}
};

/**
 * Change the visibility state of a character
 */
class FlashAnimation : public Animation {
    private:
        unsigned repetitions = 0, hideDelay = 0, showDelay = 0;
    public:
        using Me = FlashAnimation;
        Me &SetRepetitions(unsigned n) {
            repetitions = n;
            return *this;
        }
        unsigned GetRepetitions() const { return repetitions; }
        Me &SetHideDeay(unsigned d) {
            hideDelay = d;
            return *this;
        }
        unsigned GetHideDeay() const { return hideDelay; }
        Me &SetShowDeay(unsigned d) {
            showDelay = d;
            return *this;
        }
        unsigned GetShowDeay() const { return showDelay; }
        Animation *Clone() const override { return new FlashAnimation(id, repetitions, hideDelay, showDelay); }
        FlashAnimation(const std::string &_id, unsigned n, unsigned show, unsigned hide)
                : Animation(id), repetitions(n), hideDelay(hide), showDelay(show) {}
};

struct ScrollEntry {
    int dx = 0;
    int dy = 0 ;
    unsigned delay = 0;
};

/**
 * Animation for scrolling
 */
class ScrollAnimation : public Animation {
    public:
        using Scroll = std::vector<ScrollEntry>;
    private:
        Scroll scroll;
    public:
        const Scroll& GetScroll () const { return scroll; }
        void SetScroll (const Scroll& p) { scroll = p; }
        Animation*  Clone () const override
            { return new ScrollAnimation(id, scroll); }
        ScrollAnimation (const std::string& _id, const Scroll& _scroll) :
            Animation(_id), scroll(_scroll){}
};

class TickAnimation : public Animation {
    protected:
        unsigned delay = 0;
        unsigned reps = 1;
        bool isDiscrete = true; // false: when used for custom timed actions
        bool Inv () const { return isDiscrete || reps == 1; }
    public:
        using Me = TickAnimation;
        unsigned GetDelay () const { return delay; }
        Me& SetDelay (unsigned d) { delay = d; return *this; }
        unsigned GetReps () const { return reps; }
        Me& SetReps (unsigned r) { reps = r; return *this; }
        bool IsForever () const  { return !reps; }
        Me& SetForever () { reps = 0; return *this; }
        bool IsDiscrete () const  { return isDiscrete; }
        Animation* Clone () const override{
            return new TickAnimation(id, delay, reps, true);
        }
        TickAnimation (const std::string& _id, unsigned d, unsigned r, bool discrete) :
                Animation(id), delay(d), reps(r), isDiscrete(discrete) { assert(Inv());
        }
};

/***************************
 * Animator for each Category
 ***************************/

typedef uint64_t timestamp_t;
enum animatorstate_t {
    ANIMATOR_FINISHED = 0, ANIMATOR_RUNNING = 1, ANIMATOR_STOPPED= 2
};

//Animator superclass
class Animator {
    public:
        using OnFinish = std::function<void(Animator *)>;
        using OnStart = std::function<void(Animator *)>;
        using OnAction = std::function<void(Animator *, const Animation &)>;
    protected:
        std::string id ;
        timestamp_t lastTime = 0;
        animatorstate_t state = ANIMATOR_FINISHED;
        OnFinish onFinish;
        OnStart onStart;
        OnAction onAction;
        void NotifyStopped();
        void NotifyStarted();
        void NotifyAction(const Animation &);
        void Finish(bool isForced = false);
    public:
        void Stop(){
            state = ANIMATOR_STOPPED;
            NotifyStopped();
        }
        std::string GetID() {return id;}
        bool HasFinished() const { return state != ANIMATOR_RUNNING; }
        timestamp_t GetLastTime() {return lastTime;}
        virtual void TimeShift(timestamp_t offset);
        virtual void Progress(timestamp_t currTime) = 0;
        template<typename Tfunc> void SetOnFinish(const Tfunc &f) { onFinish = f; }
        template<typename Tfunc> void SetOnStart(const Tfunc &f) { onStart = f; }
        template<typename Tfunc> void SetOnAction(const Tfunc &f) { onAction = f; }
        Animator ();
        Animator (const Animator&) = delete;
        Animator (Animator&&) = delete;
        virtual ~Animator();
};

class MovingAnimator : public Animator {
    protected:
        MovingAnimation* anim = nullptr;
        unsigned currRep = 0; // animation state
    public:
        void Progress (timestamp_t currTime);
        auto GetAnim () const -> const MovingAnimation&{ return *anim; }
        void Start (MovingAnimation* a, timestamp_t t) {
            anim = a;
            lastTime = t;
            state = ANIMATOR_RUNNING;
            currRep = 0;
            NotifyStarted();
        }
        MovingAnimator () = default;
};

class FrameRangeAnimator : public Animator {
    protected:
        FrameRangeAnimation *anim = nullptr;
        unsigned currFrame = 0; // animation state
        unsigned currRep = 0; // animation state
    public:
        void Progress(timestamp_t currTime);
        unsigned GetCurrFrame() const { return currFrame; }
        unsigned GetCurrRep() const { return currRep; }
        FrameRangeAnimation *GetAnim(){return anim;}
        void Start(FrameRangeAnimation *a, timestamp_t t) {
            anim = a;
            lastTime = t;
            state = ANIMATOR_RUNNING;
            currFrame = anim->GetStartFrame();
            currRep = 0;
            NotifyStarted();
            NotifyAction(*anim);
        }
        FrameRangeAnimator(std::string id) { this->id = id; };
};

class TickAnimator : public Animator {
    protected:
        TickAnimation* anim = nullptr;
        unsigned currRep = 0;
        unsigned elapsedTime = 0; // keep track of time passed between triggers
    public:
        void Progress (timestamp_t currTime) override;
        unsigned GetCurrRep() const { return currRep; }
        unsigned GetElapsedTime() const { return elapsedTime; }
        float GetElapsedTimeNormalised () const {
            return float(elapsedTime) / float(anim->GetDelay());
        }
        void Start (const TickAnimation& a, timestamp_t t) {
            anim = (TickAnimation*) a.Clone();
            lastTime = t;
            state = ANIMATOR_RUNNING;
            currRep = 0;
            elapsedTime = 0;
            NotifyStarted();
        }
        TickAnimator () = default;
};

class AnimatorManager {
    private:
        std::set<Animator*> running, suspended;
        static AnimatorManager Manager;
    public:
        void Register (Animator* a) {
            suspended.insert(a);
        }
        void Cancel (Animator* a) {
            assert(a->HasFinished());
            suspended.erase(a);
        }
        void MarkAsRunning (Animator* a) {
            suspended.erase(a);
            running.insert(a);
        }
        void MarkAsSuspended (Animator* a){
            assert(a->HasFinished());
            running.erase(a);
            suspended.insert(a);
        }
        void Progress (timestamp_t currTime) {
            auto copied (running);
            for (auto* a : copied)
                a->Progress(currTime);
        }
        Animator* GetAnimatorByID(std::string id) {
        // Search in suspended Animators
        for (auto* a : suspended) {
            if (a->GetID() == id)
                return a;
        }
        // Search in running Animators
        for (auto* a : running) {
            if (a->GetID() == id)
                return a;
        }
        return nullptr; // Animator not found
    }


    static auto GetManager() { return Manager; }
        AnimatorManager() {};

};

void InitializeBitmaps();
void InitializeFilms();
void InitializeAnimators();

#endif //CS454_SUPER_MARIO_GAME_ANIMATION_H
