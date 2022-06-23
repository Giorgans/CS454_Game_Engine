//
// Created by Georgios Zervos on 17/11/21.
//

#include "app.h"

using namespace app;

class UnitTest1 : public App {
    public:
    static const bool NotDone() { return  false;}
    static const bool Done(){return true;}

    void Initialise(void){
            assert(al_init());
            assert(al_init_primitives_addon());
            assert(al_install_keyboard());
            assert(al_init_image_addon());
            assert(al_init_font_addon());
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