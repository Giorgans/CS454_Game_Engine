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
std::map<std::string,bool> inputs;

void input(){
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));

    while (true) {
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
           isDone = true;
           break;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) inputs.at("Down") = true;

            if(event.keyboard.keycode == ALLEGRO_KEY_A) inputs.at("A") = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) inputs.at("Right") = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) inputs.at("Left") = true;

            /**
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                     // FOR A TOP DOWN 2D GAME
                     break;
            } */
            if (event.keyboard.keycode == ALLEGRO_KEY_G) {
                if (!displayGrid)displayGrid = true;
                else displayGrid = false;

                Rendering();
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) isDone = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_COMMAND) {
                if (event.keyboard.keycode == ALLEGRO_KEY_Q) isDone = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                /*TODO
                    * implement start function*/
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_Z) {
                /*TODO
                 * implement jump function*/
                std::cout << "JUMP" << std::endl;
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP) {
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) inputs.at("Down") = false;

            if (event.keyboard.keycode == ALLEGRO_KEY_A) inputs.at("A") = false;

            if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT) inputs.at("Right") = false;

            if(event.keyboard.keycode == ALLEGRO_KEY_LEFT) inputs.at("Left") = false;
        }
        else{ break; }

        break;

    }

}
void InitializeInputs(){
    inputs.insert(std::pair<std::string ,bool>("Down",false));
    inputs.insert(std::pair<std::string ,bool>("Left",false));
    inputs.insert(std::pair<std::string ,bool>("Right",false));
    inputs.insert(std::pair<std::string ,bool>("A",false));

}