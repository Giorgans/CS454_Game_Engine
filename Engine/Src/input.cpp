//
// Created by Georgios Zervos on 15/12/21.
//

#include "../Include/input.h"
extern FrameRangeAnimator *WalkingAnimator,*DownAttackAnimator;
extern ALLEGRO_DISPLAY *window;
extern Rect DisplayArea;

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
        if (Link->GetFilm()->GetID() == DownLeft ){
            Link->SetFrame(0);
            Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
            WalkingAnimator->Start(WalkingAnimator->GetAnim(),GetSystemTime());
            WalkingAnimator->Progress(GetSystemTime());
        }
        if (Link->GetFilm()->GetID() == DownRight ){
            Link->SetFrame(0);
            Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
            WalkingAnimator->Start(WalkingAnimator->GetAnim(),GetSystemTime());
            WalkingAnimator->Progress(GetSystemTime());
        }
        Rendering();

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
           isDone = true;
           break;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){
                WalkingAnimator->Stop();
                if (Link->GetFilm()->GetID() == WalkingLeft ){
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(DownLeft));
                }
                if (Link->GetFilm()->GetID() == WalkingRight ){
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(DownRight));
                }
                Link->SetFrame(0);
                Rendering();
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                if (Link->GetFilm()->GetID() == WalkingRight) {
                    WalkingAnimator->Progress(GetSystemTime());
                }
                else if (Link->GetFilm()->GetID() == WalkingLeft || Link->GetFilm()->GetID() == DownLeft || Link->GetFilm()->GetID() == DownRight) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingRight));
                    WalkingAnimator->Start(WalkingAnimator->GetAnim(),GetSystemTime());
                    WalkingAnimator->Progress(GetSystemTime());
                }
                if( ((terrain->GetViewWindow().x + terrain->GetViewWindow().w) - (terrain->GetViewWindow().x/2)) <= Link->GetBox().x){
                    background->Scroll(4, 0);
                    terrain->Scroll(4, 0);
                }
                Link->SetHasDirectMotion(true).Move(4,0).SetHasDirectMotion(false);
                Link->SetFrame(WalkingAnimator->GetCurrFrame());
                break;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                if (Link->GetFilm()->GetID() == WalkingLeft) {
                    WalkingAnimator->Progress(GetSystemTime());
                }
                if (Link->GetFilm()->GetID() == WalkingRight || Link->GetFilm()->GetID() == DownLeft || Link->GetFilm()->GetID() == DownRight) {
                    Link->SetFilm(AnimationFilmHolder::GetHolder().Load(WalkingLeft));
                    WalkingAnimator->Start(WalkingAnimator->GetAnim(),GetSystemTime());
                    WalkingAnimator->Progress(GetSystemTime());
                }
                if( ((terrain->GetViewWindow().x - 4 ) >= 0) && ((terrain->GetViewWindow().x + terrain->GetViewWindow().w/2) ) <= Link->GetBox().x ){
                    background->Scroll(-4, 0);
                    terrain->Scroll(-4, 0);
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
            else if(event.keyboard.keycode == ALLEGRO_KEY_G){
                if(!displayGrid)displayGrid=true;
                else displayGrid=false;
                break;
            }

            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
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
                WalkingAnimator->Stop();

                /*TODO
                 * implement jump function*/
                std::cout<<"JUMP"<<std::endl;

            }
            else{}




        }
        else {
        }


}

}
