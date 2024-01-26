#include "../Include/animation.h"
#include "../Include/rendering.h"


AnimationFilmHolder  AnimationFilmHolder::holder ;
AnimatorManager AnimatorManager::Manager  ;
BitmapLoader BitmapLoader::Loader  ;
extern std::map<std::string,bool> inputs;

uint64_t GameTime = 0;
void SetGameTime() { GameTime = GetSystemTime (); }
uint64_t GetGameTime(){ return GameTime; }

void Animations(){
    AnimatorManager manager = AnimatorManager::GetManager();
    manager.Progress(GetGameTime());
}


void AnimationFilm::DisplayFrame (ALLEGRO_BITMAP *dest, const Point& at, byte frameNo) const
{BitmapBlit(bitmap,GetFrameBox(frameNo),dest,at);}


/***************************************
 *  Animation Film Holder implementation
 **************************************/
void AnimationFilmHolder::CleanUp() {
    for (auto &i: films)
        delete (i.second);
    films.clear();
}

auto AnimationFilmHolder::GetFilm(const std::string &id) -> const AnimationFilm *const {
    auto i = films.find(id);
    return i != films.end() ? i->second : nullptr;
}

/***************************************
 *  Animators implementation
 **************************************/

void Animator::Finish(bool isForced) {
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

void FrameRangeAnimator::Progress (timestamp_t currTime) {
    while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {
        if (currFrame == anim->GetEndFrame()) {
            assert(anim->IsForever() || (currRep && currRep < anim->GetReps()));
            currFrame = anim->GetStartFrame(); // flip to start
        } else
            ++currFrame;

        lastTime += anim->GetDelay();
        NotifyAction(*anim);

        if (currFrame == anim->GetEndFrame()) {
            if (!anim->IsForever() && ++currRep == anim->GetReps()) {
                state = ANIMATOR_FINISHED;
                NotifyStopped();
                return;
            }
        }
        if (currFrame > anim->GetEndFrame()) {
            currFrame = anim->GetStartFrame(); // flip to start
        }
    }
}

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





