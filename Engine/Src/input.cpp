//
// Created by Georgios Zervos on 15/12/21.
//

#include "../Include/input.h"
#include "../Include/terrain.h"

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
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            /*TODO
             * replace assert(0) with a smoother quit without errors*/
           isDone = true;
           break;

        }
        else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                background->Scroll(8, 0);
                terrain->Scroll(8, 0);
                break;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                background->Scroll(-16, 0);
                terrain->Scroll(-16, 0);
                break;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                // FOR A TOP DOWN 2D GAME
                break;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                // FOR A TOP DOWN 2D GAME
                break;
            }
            else if(event.keyboard.keycode == ALLEGRO_KEY_G){
                // std::cout<<"GRID DISPLAY"<<std::endl;
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
            else if(event.keyboard.keycode == ALLEGRO_KEY_X){
                /*TODO
                 * implement run function*/
                std::cout<<"RUN"<<std::endl;
            }

        }
}

}
