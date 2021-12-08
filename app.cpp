//
// Created by Georgios Zervos on 17/11/21.
//

#include "app.h"
#include <iostream>
#include <allegro5/allegro.h>
//#include <allegro5/allegro_osx.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include <png.h>

using namespace app;
class UnitTest1 : public App {
    public:
        void Initialise(void){
            assert(al_init());
            assert(al_init_primitives_addon());
            assert(al_install_keyboard());
            assert(al_init_image_addon());
            assert(al_init_font_addon());
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