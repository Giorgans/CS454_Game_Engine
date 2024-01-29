
#include "app.h"

using namespace app;

class ZeldaII: public App {
public:
    static const bool NotDone() { return  false;}
    static const bool Done(){return true;}

    void Initialise(void){

        assert(al_init());
        assert(al_init_primitives_addon());
        assert(al_install_keyboard());
        assert(al_install_audio());
        assert(al_init_image_addon());
        assert(al_init_font_addon());
        assert(al_init_acodec_addon());

        GetGame().SetDone(NotDone);
        GetGame().SetRender(ZeldaII_Rendering);
        GetGame().SetInput(ZeldaII_Input);
        GetGame().SetProgressAnimations(Animations);
        GetGame().SetSound(ZeldaII_Sound);
        GetGame().SetPhysics( ZeldaII_Physics);

        InitializeInputs();
        InitializeBitmaps();
        InitializeFilms();
        InitializeSprites();
        InitializeRendering();
        InitializeAnimations();
        InitializeSounds();
    }
    void Load(void){  }
    void Clear(void){  }
};


int main(int argc, char **argv)
{
    ZeldaII app;
    app.Main();
    return 0;
}