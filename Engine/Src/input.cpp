//
// Created by Georgios Zervos on 15/12/21.
//

#include "../Include/input.h"
extern FrameRangeAnimator *WalkingAnimator,*DownAttackAnimator;
extern ALLEGRO_DISPLAY *window;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;
bool isDone = false;
extern bool displayGrid;

void input(){
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));

    while (true) {
        al_wait_for_event(event_queue, &event);
        Sprite * Link =  SpriteManager::GetSingleton().GetDisplayList().at(0);
        FrameRangeAnimation *WalkingAnimation = new FrameRangeAnimation("Walking",0,AnimationFilmHolder::GetHolder().GetFilm(WalkingRight)->GetTotalFrames()-1,0,32,0,150);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
           isDone = true;
           break;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                if (Link->GetFilm()->GetID() == WalkingRight) {
                    WalkingAnimator->Progress(GetSystemTime());
                }
                else if (Link->GetFilm()->GetID() == WalkingLeft) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                    WalkingAnimator->Progress(GetSystemTime());
                }
                else {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                    WalkingAnimator->Start(WalkingAnimator->GetAnim(),GetSystemTime());
                    WalkingAnimator->Progress(GetSystemTime());
                }
                //background->Scroll(8, 0);
                //terrain->Scroll(8, 0);
                int dx = 4,dy=0;
                //Rect box = Link->GetBox();
                //terrain->GetGrid()->FilterGridMotion(box, &dx, &dy);
                Link->SetHasDirectMotion(true).Move(dx,0).SetHasDirectMotion(false);
                Link->SetFrame(WalkingAnimator->GetCurrFrame());
                break;
            }

            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                if (Link->GetFilm()->GetID() == WalkingLeft) {
                    WalkingAnimator->Progress(GetSystemTime());
                }
                if (Link->GetFilm()->GetID() == WalkingRight) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                    WalkingAnimator->Progress(GetSystemTime());
                }
                else {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                    WalkingAnimator->Start(WalkingAnimator->GetAnim(),GetSystemTime());
                    WalkingAnimator->Progress(GetSystemTime());
                }
                //background->Scroll(-8, 0);
                //terrain->Scroll(-8, 0);
                int dx = -4,dy=0;
                Link->SetHasDirectMotion(true).Move(dx,0).SetHasDirectMotion(false);
                Link->SetFrame(WalkingAnimator->GetCurrFrame());

                break;
            }
            /**
            else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                // FOR A TOP DOWN 2D GAME
                break;
            } */
            else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                WalkingAnimator->Stop();
                if (Link->GetFilm()->GetID() == WalkingLeft ) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));
                    Link->SetFrame(0);

                }
                else if (Link->GetFilm()->GetID() == WalkingRight ) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));
                    Link->SetFrame(0);
                }
                break;
            }

            else if(event.keyboard.keycode == ALLEGRO_KEY_G){
                if(!displayGrid)displayGrid=true;
                else displayGrid=false;
                break;
            }

            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                /*TODO
                    * replace assert(0) with a smoother quit without errors*/
                isDone = true;
                break;
            }
            if(event.keyboard.keycode == ALLEGRO_KEY_COMMAND){
                if(event.keyboard.keycode == ALLEGRO_KEY_Q ) {
                    isDone = true;
                    break;
                }

            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                /*TODO
                    * implement start function*/
            }

            else if(event.keyboard.keycode == ALLEGRO_KEY_Z){
                /*TODO
                 * implement jump function*/
                std::cout<<"JUMP"<<std::endl;

            }
            else if(event.keyboard.keycode == ALLEGRO_KEY_A){
                if(Link->GetFilm()->GetID() == DownRight || Link->GetFilm()->GetID() == DownLeft){
                    Link->SetFrame(1);
                }
                break;
            }

        }
}

}
