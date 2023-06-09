//
// Created by Georgios Zervos on 6/11/22.
//
#include "../Include/animation.h"
AnimationFilmHolder  AnimationFilmHolder::holder ;
AnimatorManager AnimatorManager::Manager  ;
BitmapLoader BitmapLoader::Loader  ;

static unsigned long currT = 0;
void setgametime() { currT = GetSystemTime (); }
unsigned long getgametime(){ return currT; }

/***************************************
 *  Animation Film Holder implementation
 **************************************/
/** void AnimationFilmHolder::Load (const std::string& text, const EntryParser& entryParser) {
    int pos = 0;
    while (true) {
        std::string id, path;
        std::vector<Rect> rects;
        auto i = entryParser(pos, text, id, path, rects);
        assert(i >= 0);
        if (!i) return;
        pos += i;
        assert(!GetFilm(id));
        films[id] = new AnimationFilm(BitmapLoader::GetLoader().Load(path), rects, id);
    }

}

void AnimationFilmHolder::Load (const std::string& text, const Parser& parser) {
    std::list<AnimationFilm> output;
    auto result = parser(output, text);
    assert(result);
    for (auto &entry: output) {
        assert(!GetFilm(entry.GetID()));
        films[entry.GetID()] = new AnimationFilm(BitmapLoader::GetLoader().Load(entry.GetID()), entry.GetBoxes(), entry.GetID());
    }
}
**/
void AnimationFilmHolder::CleanUp () {
    for (auto& i : films)
        delete(i.second);
    films.clear();
}

auto AnimationFilmHolder::GetFilm (const std::string& id) -> const AnimationFilm* const {
        auto i = films.find(id);
        return i != films.end() ? i->second : nullptr;
}

/***************************************
 *  Animators implementation
 **************************************/

void Animator::Finish (bool isForced) {
    if (!HasFinished()) {
        state = isForced ? ANIMATOR_STOPPED : ANIMATOR_FINISHED; NotifyStopped();
    }
}


void Animator::NotifyAction (const Animation& anim) {
    if (onAction)
        (onAction)(this, anim);
}
void Animator::TimeShift (timestamp_t offset) {
    lastTime += offset;
}

void Animator::NotifyStopped() {
    AnimatorManager::GetManager().MarkAsSuspended(this);
    if (onFinish)
        (onFinish)(this);
}

void Animator::NotifyStarted() {
    AnimatorManager::GetManager().MarkAsRunning(this);
    if (onStart)
        (onStart)(this);
}
Animator::Animator () {
    AnimatorManager::GetManager().Register(this);
}

Animator::~Animator(){
    AnimatorManager::GetManager().Cancel(this);
}

void MovingAnimator::Progress (timestamp_t currTime) {
    while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {
        lastTime += anim->GetDelay();
        NotifyAction(*anim);
        if (!anim->IsForever() && ++currRep == anim->GetReps()) {
            state = ANIMATOR_FINISHED;
            NotifyStopped();
            return;
        }
    }
}
/*
void Sprite_MoveAction (Sprite* sprite, const MovingAnimation& anim) {
    sprite->Move(anim.GetDx(), anim.GetDy());
}

animator->SetOnAction(
[sprite](Animator* animator, const Animation& anim) {
assert(dynamic_cast<const MovingAnimation*>(&anim));
Sprite_MoveAction(
        sprite,
(const MovingAnimation&)anim );
} ); */

void FrameRangeAnimator::Progress (timestamp_t currTime) {
    while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {
        if (currFrame == anim->GetEndFrame()) { assert(anim->IsForever() || currRep < anim->GetReps()); currFrame = anim->GetStartFrame(); // flip to start
        }
        else
            ++currFrame;
        lastTime += anim->GetDelay();
        NotifyAction(*anim);
        if (currFrame == anim->GetEndFrame())
            if (!anim->IsForever() && ++currRep == anim->GetReps()) {
                state = ANIMATOR_FINISHED;
                NotifyStopped();
                return;
            }
    }
}

/**
void FrameRange_Action (Sprite* sprite, Animator* animator, const FrameRangeAnimation& anim) { auto* frameRangeAnimator = (FrameRangeAnimator*) animator;
    if (frameRangeAnimator->GetCurrFrame() != anim.GetStartFrame() ||
        frameRangeAnimator->GetCurrRep()) sprite->Move(anim.GetDx(), anim.GetDy());
    sprite->SetFrame(frameRangeAnimator->GetCurrFrame());
}

    animator->SetOnAction([sprite](Animator* animator, const Animation& anim) {
} );
 */

void TickAnimator::Progress (timestamp_t currTime) {
    if (!anim->IsDiscrete()) { // no discrete fires in every loop!
        elapsedTime = currTime - lastTime;
        lastTime = currTime;
        NotifyAction(*anim);
    }
    else
        while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {
            lastTime += anim->GetDelay();
            NotifyAction(*anim);
            if (!anim->IsForever() && ++currRep == anim->GetReps()) {
                state = ANIMATOR_FINISHED;
                NotifyStopped();
                return;
            }
        }
}




/**
* Initialization
*/
void InitializeBitmaps(){
    for(auto const f : std::__fs::filesystem::directory_iterator(AnimationBitmaps)){
       if(f.path().filename()!=".DS_Store") // hidden file on mac folder
        BitmapLoader::GetLoader().Store(f.path().filename(), al_load_bitmap( f.path().string().c_str()) );
    }
    std::cout << "size: " << BitmapLoader::GetLoader().bitmaps.size() << std::endl;
}

void InitializeFilms(){
    for(auto const f : std::__fs::filesystem::directory_iterator(AnimationBitmaps)) {
        if (f.path().filename() != ".DS_Store") { // hidden file on mac folder
            ALLEGRO_BITMAP *bitmap = BitmapLoader::GetLoader().Load(f.path().filename());
            std::cout << "name: " << f.path().filename() << std::endl;
            if (bitmap == NULL)assert(false);
            int frames = int(al_get_bitmap_width(bitmap) / 32);
            std::vector<Rect> boxes = {};
            for (int i = 0; i < frames; i++)
                boxes.push_back({i * 32, 0, 32, 32});
            AnimationFilm *film = new AnimationFilm(bitmap, boxes, f.path().filename());

            AnimationFilmHolder::GetHolder().Store(f.path().filename(), film);

        }
    }
}




