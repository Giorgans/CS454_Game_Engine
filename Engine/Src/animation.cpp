//
// Created by Georgios Zervos on 6/11/22.
//
#include "../Include/animation.h"
#include "../Include/input.h"
#include "../Include/rendering.h"


AnimationFilmHolder  AnimationFilmHolder::holder ;
AnimatorManager AnimatorManager::Manager  ;
BitmapLoader BitmapLoader::Loader  ;
extern FrameRangeAnimator *PlayerAnimator;
extern std::map<std::string,bool> inputs;

uint64_t currT = 0;
void setgametime() { currT = GetSystemTime (); }
uint64_t getgametime(){ return currT; }

void Animations(){

    Sprite * Player =  SpriteManager::GetSingleton().GetDisplayList().at(0);
    auto *AttackRightAnimation = new FrameRangeAnimation("AttackRight",0,AnimationFilmHolder::GetHolder().GetFilm(AttackRight)->GetTotalFrames()-1,0,0,0,1000/3);
    auto *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,4,0,1000/10);

    if(inputs.at("locked")){
        if(Player->GetFilm()->GetID() == AttackRight || Player->GetFilm()->GetID() == AttackLeft ){
            PlayerAnimator->Progress(getgametime());
            Player->SetFrame(PlayerAnimator->GetCurrFrame());
            if(PlayerAnimator->GetCurrFrame() == PlayerAnimator->GetAnim()->GetEndFrame())
                inputs.at("locked") = false;

            if(!inputs.at("locked")){
                inputs.at("A") = false;
                if (Player->GetFilm()->GetID() == AttackRight) {
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));

                } else if (Player->GetFilm()->GetID() == AttackLeft) {
                    Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                }

                PlayerAnimator->Start(WalkingAnimation, getgametime());
                FrameRange_Action(Player, PlayerAnimator, *PlayerAnimator->GetAnim());
            }
        }
    }
    else {
        if (inputs.at("Down")) {
            PlayerAnimator->Stop();
            if (Player->GetFilm()->GetID() == WalkingLeft)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));

            if (Player->GetFilm()->GetID() == WalkingRight)
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));

            Player->SetFrame(0);
        } else {
            if (Player->GetFilm()->GetID() == DownLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                Player->SetFrame(0);
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), getgametime());
                PlayerAnimator->Progress(getgametime());
            }
            if (Player->GetFilm()->GetID() == DownRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                Player->SetFrame(0);
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), getgametime());
                PlayerAnimator->Progress(getgametime());
            }
        }

        if (inputs.at("Down") && inputs.at("A"))
            Player->SetFrame(1);


        if (inputs.at("Right") && !inputs.at("Down")) {
            if (Player->GetFilm()->GetID() == WalkingRight)
                PlayerAnimator->Progress(getgametime());
            else if (Player->GetFilm()->GetID() == WalkingLeft || Player->GetFilm()->GetID() == DownLeft ||
                     Player->GetFilm()->GetID() == DownRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), getgametime());
                PlayerAnimator->Progress(getgametime());
            }
            if (((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x / 2)) <=
                Player->GetBox().x) {
                background->Scroll(4, 0);
                terrain->Scroll(4, 0);
            }
            int dx = PlayerAnimator->GetAnim()->GetDx();

            terrain->GetGrid()->FilterGridMotionRight(Player->GetBox(), &dx);
            Player->SetHasDirectMotion(true).Move(dx, 0);

            Player->SetFrame(PlayerAnimator->GetCurrFrame());

        }

        if (inputs.at("Left") && !inputs.at("Down")) {
            if (Player->GetFilm()->GetID() == WalkingLeft) {
                PlayerAnimator->Progress(getgametime());
            }
            if (Player->GetFilm()->GetID() == WalkingRight || Player->GetFilm()->GetID() == DownLeft ||
                Player->GetFilm()->GetID() == DownRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                PlayerAnimator->Start(PlayerAnimator->GetAnim(), getgametime());
                PlayerAnimator->Progress(getgametime());
            }
            if (((terrain->GetViewWindow().x - 4) >= 0) &&
                ((terrain->GetViewWindow().x + terrain->GetViewWindow().w / 2)) <= Player->GetBox().x) {
                background->Scroll(-4, 0);
                terrain->Scroll(-4, 0);
            }

            int dx = -PlayerAnimator->GetAnim()->GetDx();

            terrain->GetGrid()->FilterGridMotionLeft(Player->GetBox(), &dx);
            Player->SetHasDirectMotion(true).Move(dx, 0);

            Player->SetFrame(PlayerAnimator->GetCurrFrame());

        }

        if (inputs.at("A") && !inputs.at("Down")) {
            PlayerAnimator->Stop();

            inputs.at("locked")= true;
            if (Player->GetFilm()->GetID() == WalkingRight) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackRight));

            } else if (Player->GetFilm()->GetID() == WalkingLeft) {
                Player->SetFilm(AnimationFilmHolder::GetHolder().Load(AttackLeft));
            }
            inputs.at("A") = false;
            PlayerAnimator->Start(AttackRightAnimation, getgametime());
            PlayerAnimator->Progress(getgametime());
            Player->SetFrame(0);

        }
    }
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





