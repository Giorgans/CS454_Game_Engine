#include "../ZeldaII.h"
#include "../../../Engine/Include/terrain.h"
#include <map>
extern ALLEGRO_DISPLAY *window;
extern Rect DisplayArea;

std::map<std::string,bool> inputs;

void ZeldaII_Input(){

    if(!inputs["start"])
        TitleScreenInputs();
    else
        MainGameInputs();

}

void TitleScreenInputs() {
    ALLEGRO_KEYBOARD_STATE keyboardState;
    al_get_keyboard_state(&keyboardState);
    if(al_key_down(&keyboardState, ALLEGRO_KEY_ENTER))
        inputs["start"] = true;

    if(al_key_down(&keyboardState, ALLEGRO_KEY_ESCAPE))
        inputs["exit"] = true;




}

void MainGameInputs(){
    ALLEGRO_KEYBOARD_STATE keyboardState;
    al_get_keyboard_state(&keyboardState);

    inputs["Right"] = al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT);
    inputs["Left"] = al_key_down(&keyboardState, ALLEGRO_KEY_LEFT);
    inputs["Up"] = al_key_down(&keyboardState, ALLEGRO_KEY_UP);
    inputs["Down"] = al_key_down(&keyboardState, ALLEGRO_KEY_DOWN);
    inputs["A"] = al_key_down(&keyboardState, ALLEGRO_KEY_A);
    inputs["S"] = al_key_down(&keyboardState, ALLEGRO_KEY_S);
    inputs["G"] = al_key_down(&keyboardState, ALLEGRO_KEY_G);
    inputs["F"] = al_key_down(&keyboardState, ALLEGRO_KEY_F);

    if(inputs["F"])
        inputs["FullScreen"]= !inputs["FullScreen"];
    if(al_key_down(&keyboardState, ALLEGRO_KEY_ESCAPE))
        inputs["exit"] = true;
}

void InitializeInputs(){
    inputs.insert(std::pair<std::string ,bool>("Up",false));
    inputs.insert(std::pair<std::string ,bool>("Down",false));
    inputs.insert(std::pair<std::string ,bool>("Left",false));
    inputs.insert(std::pair<std::string ,bool>("Right",false));
    inputs.insert(std::pair<std::string ,bool>("A",false));
    inputs.insert(std::pair<std::string ,bool>("S",false));
    inputs.insert(std::pair<std::string ,bool>("G",false));
    inputs.insert(std::pair<std::string ,bool>("start",false));
    inputs.insert(std::pair<std::string ,bool>("exit",false));
    inputs.insert(std::pair<std::string ,bool>("locked",false));
    inputs.insert(std::pair<std::string ,bool>("key",false));
    inputs.insert(std::pair<std::string ,bool>("center",false));
    inputs.insert(std::pair<std::string ,bool>("F",false));
    inputs.insert(std::pair<std::string ,bool>("FullScreen",false));

}