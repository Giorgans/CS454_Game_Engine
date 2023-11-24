//
// Created by Georgios Zervos on 6/11/22.
//
#include "../Include/animation.h"
#include "../Include/input.h"

AnimationFilmHolder  AnimationFilmHolder::holder ;
AnimatorManager AnimatorManager::Manager  ;
BitmapLoader BitmapLoader::Loader  ;
extern FrameRangeAnimator *LinkAnimator;
extern std::map<std::string,bool> inputs;

uint64_t currT = 0;
void setgametime() { currT = GetSystemTime (); }
uint64_t getgametime(){ return currT; }

void Animations(){

    Sprite * Link =  SpriteManager::GetSingleton().GetDisplayList().at(0);
    auto *AttackRightAnimation = new FrameRangeAnimation("AttackRight",0,AnimationFilmHolder::GetHolder().GetFilm(AttackRight)->GetTotalFrames()-1,0,0,0,1000/3);
    auto *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,1000/10);

    if(inputs.at("locked")){
        if(Link->GetFilm()->GetID() == AttackRight || Link->GetFilm()->GetID() == AttackLeft ){
            LinkAnimator->Progress(getgametime());
            Link->SetFrame(LinkAnimator->GetCurrFrame());
            if(LinkAnimator->GetCurrFrame() == LinkAnimator->GetAnim()->GetEndFrame())
                inputs.at("locked") = false;

            if(!inputs.at("locked")){
                inputs.at("A") = false;
                if (Link->GetFilm()->GetID() == AttackRight) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));

                } else if (Link->GetFilm()->GetID() == AttackLeft) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                }

                LinkAnimator->Start(WalkingAnimation, getgametime());
                FrameRange_Action(Link, LinkAnimator, *LinkAnimator->GetAnim());
            }
        }
    }
    else {
        if (inputs.at("Down")) {
            LinkAnimator->Stop();
            if (Link->GetFilm()->GetID() == WalkingLeft)
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));

            if (Link->GetFilm()->GetID() == WalkingRight)
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));

            Link->SetFrame(0);
        } else {
            if (Link->GetFilm()->GetID() == DownLeft) {
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                Link->SetFrame(0);
                LinkAnimator->Start(LinkAnimator->GetAnim(), getgametime());
                LinkAnimator->Progress(getgametime());
            }
            if (Link->GetFilm()->GetID() == DownRight) {
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                Link->SetFrame(0);
                LinkAnimator->Start(LinkAnimator->GetAnim(), getgametime());
                LinkAnimator->Progress(getgametime());
            }
        }

        if (inputs.at("Down") && inputs.at("A"))
            Link->SetFrame(1);


        if (inputs.at("Right") && !inputs.at("Down")) {
            if (Link->GetFilm()->GetID() == WalkingRight)
                LinkAnimator->Progress(getgametime());
            else if (Link->GetFilm()->GetID() == WalkingLeft || Link->GetFilm()->GetID() == DownLeft ||
                     Link->GetFilm()->GetID() == DownRight) {
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                LinkAnimator->Start(LinkAnimator->GetAnim(), getgametime());
                LinkAnimator->Progress(getgametime());
            }
            if (((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x / 2)) <=
                Link->GetBox().x) {
                background->Scroll(4, 0);
                terrain->Scroll(4, 0);
            }
            int dx = 4;

            terrain->GetGrid()->FilterGridMotionRight(Link->GetBox(),&dx);
            Link->SetHasDirectMotion(true).Move(dx,0);
            Link->SetFrame(LinkAnimator->GetCurrFrame());

        }

        if (inputs.at("Left") && !inputs.at("Down")) {
            if (Link->GetFilm()->GetID() == WalkingLeft) {
                LinkAnimator->Progress(getgametime());
            }
            if (Link->GetFilm()->GetID() == WalkingRight || Link->GetFilm()->GetID() == DownLeft ||
                Link->GetFilm()->GetID() == DownRight) {
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                LinkAnimator->Start(LinkAnimator->GetAnim(), getgametime());
                LinkAnimator->Progress(getgametime());
            }
            if (((terrain->GetViewWindow().x - 4) >= 0) &&
                ((terrain->GetViewWindow().x + terrain->GetViewWindow().w / 2)) <= Link->GetBox().x) {
                background->Scroll(-4, 0);
                terrain->Scroll(-4, 0);
            }
            //background->Scroll(-8, 0);
            //terrain->Scroll(-8, 0);
            int dx = -4, dy = 0;
            Link->SetHasDirectMotion(true).Move(dx, 0);
            Link->SetFrame(LinkAnimator->GetCurrFrame());

        }

        if (inputs.at("A") && !inputs.at("Down")) {
            LinkAnimator->Stop();

            inputs.at("locked")= true;
            if (Link->GetFilm()->GetID() == WalkingRight) {
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackRight));

            } else if (Link->GetFilm()->GetID() == WalkingLeft) {
                Link->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackLeft));
            }
            inputs.at("A") = false;
            LinkAnimator->Start(AttackRightAnimation, getgametime());
            LinkAnimator->Progress(getgametime());
            Link->SetFrame(0);

        }
    }
}

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
//
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

void FrameRangeAnimator::Progress (timestamp_t currTime) {
    while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {
        if (currFrame == anim->GetEndFrame()) {
            assert(anim->IsForever() || currRep < anim->GetReps());
            currFrame = anim->GetStartFrame(); // flip to start
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
}

void InitializeFilms(){
    for(auto const f : std::__fs::filesystem::directory_iterator(AnimationBitmaps)) {
        if (f.path().filename() != ".DS_Store") { // hidden file on mac folder
            ALLEGRO_BITMAP *bitmap = BitmapLoader::GetLoader().Load(f.path().filename());
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

FrameRangeAnimator *LinkAnimator = new FrameRangeAnimator("LinkAnimator");

uint64_t FRAME_RATE = 24;            // Frames per second
uint64_t FRAME_DURATION = 1000 / FRAME_RATE;  // Duration of each frame

void InitializeAnimators(){
    auto *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,FRAME_DURATION);

    LinkAnimator->Start(WalkingAnimation,GetSystemTime());

    auto link = SpriteManager::GetSingleton().GetDisplayList().at(0);
    link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
    LinkAnimator->SetOnAction([link](Animator* animator, const Animation& anim) {} );

}



