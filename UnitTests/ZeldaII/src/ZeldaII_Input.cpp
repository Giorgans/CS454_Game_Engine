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
    ALLEGRO_KEYBOARD_STATE keyboardState;
    al_get_keyboard_state(&keyboardState);

    inputs["Right"] = al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT);
    inputs["Left"] = al_key_down(&keyboardState, ALLEGRO_KEY_LEFT);
    inputs["Down"] = al_key_down(&keyboardState, ALLEGRO_KEY_DOWN);
    inputs["A"] = al_key_down(&keyboardState, ALLEGRO_KEY_A);
    inputs["G"] = al_key_down(&keyboardState, ALLEGRO_KEY_G);

    if(al_key_down(&keyboardState, ALLEGRO_KEY_ESCAPE))
        inputs["exit"] = true;

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