//
// Created by Georgios Zervos on 15/12/21.
//

#include "../Include/input.h"
#include "../Include/rendering.h"
extern ALLEGRO_DISPLAY window;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;
void input(void){
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    while (true) {
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            assert(0);
        }
        if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                background->Scroll(16, 0);
                terrain->Scroll(16, 0);
                break;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                background->Scroll(-16, 0);
                terrain->Scroll(-16, 0);
                break;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                background->Scroll(0, 8);
                terrain->Scroll(0, 8);
                break;
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                background->Scroll(0, -8);
                terrain->Scroll(0, -8);
                break;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                assert(0);
            }
        }
    }

}