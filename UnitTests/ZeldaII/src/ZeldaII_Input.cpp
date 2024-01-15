#include "../ZeldaII.h"
#include "../../../Engine/Include/terrain.h"
#include <map>
extern ALLEGRO_DISPLAY *window;
extern Rect DisplayArea;

std::map<std::string,bool> inputs;
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;

void ZeldaII_Input(){
    if(!event_queue) {
        event_queue = al_create_event_queue();
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_display_event_source(window));
    }

    if(!inputs.at("start"))
        TitleScreenInputs();
    else
        MainGameInputs();

}

void TitleScreenInputs() {
    ALLEGRO_EVENT event;

    // Check if there's an event and process it
    if (al_get_next_event(event_queue, &event)) {
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                inputs["start"] = true;
            }
        }
    }

    // Other non-blocking code (like animation updates) goes here
}

void MainGameInputs(){
    ALLEGRO_EVENT event;

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));

    if(!inputs.at("locked") )
        al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        inputs.at("exit") = true;

    if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            inputs.at("exit") = true;

        if (event.keyboard.keycode == ALLEGRO_KEY_COMMAND)
            if (event.keyboard.keycode == ALLEGRO_KEY_Q)
                inputs.at("exit") = true;

        if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            inputs.at("Down") = true;

        if(event.keyboard.keycode == ALLEGRO_KEY_A)
            inputs.at("A") = true;

        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            inputs.at("Right") = true;

        if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
            inputs.at("Left") = true;

        if (event.keyboard.keycode == ALLEGRO_KEY_G)
            inputs.at("G") = true;

        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            inputs.at("start") = true;

        if (event.keyboard.keycode == ALLEGRO_KEY_Z) {}

    }
    if(event.type == ALLEGRO_EVENT_KEY_UP) {
        if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            inputs.at("Down") = false;

        if (event.keyboard.keycode == ALLEGRO_KEY_A)
            inputs.at("A") = false;

        if (event.keyboard.keycode == ALLEGRO_KEY_G)
            inputs.at("G") = false;

        if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            inputs.at("Right") = false;

        if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
            inputs.at("Left") = false;
    }
    else{}

}
void InitializeInputs(){
    inputs.insert(std::pair<std::string ,bool>("Down",false));
    inputs.insert(std::pair<std::string ,bool>("Left",false));
    inputs.insert(std::pair<std::string ,bool>("Right",false));
    inputs.insert(std::pair<std::string ,bool>("A",false));
    inputs.insert(std::pair<std::string ,bool>("G",false));
    inputs.insert(std::pair<std::string ,bool>("start",false));
    inputs.insert(std::pair<std::string ,bool>("exit",false));
    inputs.insert(std::pair<std::string ,bool>("locked",false));

}