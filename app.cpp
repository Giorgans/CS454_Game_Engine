//
// Created by Georgios Zervos on 17/11/21.
//

#include "app.h"

#include <png.h>

#define DISPLAY_W 640
#define DISPLAY_H 480

using namespace app;
class UnitTest1 : public App {
    private:
        ALLEGRO_DISPLAY *window;
        static const bool NotDone() { return false;}
        static const bool Done() { return false; }
    public:
        void Initialise(void){
            assert(al_init());
            assert(al_init_primitives_addon());
            assert(al_install_keyboard());
            assert(al_init_image_addon());
            assert(al_init_font_addon());
            GetGame().SetDone(NotDone);
            this->window = al_create_display(DISPLAY_W,DISPLAY_H);
            assert(window);
        }
        void Load(void){  }
        void Clear(void){  }
};

int main(int argc, char **argv)
{
    UnitTest1 app;
    app.Main();
    return 0;
}