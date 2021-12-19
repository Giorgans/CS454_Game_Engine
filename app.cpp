//
// Created by Georgios Zervos on 17/11/21.
//

#include "app.h"

#include <png.h>
using namespace app;
ALLEGRO_DISPLAY *window;

class UnitTest1 : public App {
    private:
        static const bool NotDone() { return false;}
        static const bool Done() { return false; }
    public:
        void Initialise(void){
            assert(al_init());
            assert(al_init_primitives_addon());
            assert(al_install_keyboard());
            assert(al_init_image_addon());
            assert(al_init_font_addon());
            window = al_create_display(DISPLAY_W,DISPLAY_H);
            ALLEGRO_BITMAP *icon = al_load_bitmap(ICON_FILE_PATH);
            al_set_display_icon(window, icon);
            GetGame().SetDone(NotDone);
            GetGame().SetRender(Rendering);
            GetGame().SetInput(input);

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