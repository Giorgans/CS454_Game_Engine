//
// Created by Georgios Zervos on 15/12/21.
//

#include "../Include/input.h"

extern ALLEGRO_DISPLAY *window;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;

void input(){
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));

    while (true) {
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            /*TODO
             * replace assert(0) with a smoother quit without errors*/
            //done=true;
           assert(0);

        }
       else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {

            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                background->Scroll(16, 0);
                terrain->Scroll(16, 0);
                break;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                background->Scroll(-16, 0);
                terrain->Scroll(-16, 0);
                break;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                background->Scroll(0, 8);
                terrain->Scroll(0, 8);
                break;
            }

           else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                background->Scroll(0, -8);
                terrain->Scroll(0, -8);
                break;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                /*TODO
                    * replace assert(0) with a smoother quit without errors*/
                //done=true;
                assert(0);
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                /*TODO
                    * implement start function*/
                //done=true;

            }

            else if(event.keyboard.keycode == ALLEGRO_KEY_Z){
                /*TODO
                 * implement jump function*/
                std::cout<<"JUMP"<<std::endl;

            }
            else if(event.keyboard.keycode == ALLEGRO_KEY_X){
                /*TODO
                 * implement run function*/
                std::cout<<"RUN"<<std::endl;

            }

        }
}

}
