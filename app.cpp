
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
        InitializeRendering();
        InitializeBitmaps();
        InitializeFilms();
        InitializeSprites();
        InitializeRendering();
        InitializeAnimations();
        InitializeSounds();
    }
    void Load(void){  }
    void Clear(void){
        BitmapLoader::GetLoader().CleanUp();
        AnimationFilmHolder::GetHolder().CleanUp();
        AnimatorManager::GetManager().CleanUp();
        SpriteManager::GetSingleton().CleanUp();
        SoundManager::GetManager().CleanUp();

        al_uninstall_audio();
        al_uninstall_keyboard();
        al_shutdown_font_addon();
        al_shutdown_primitives_addon();
        al_shutdown_image_addon();
        al_uninstall_system();

    }
};


int main(int argc, char **argv)
{
    ZeldaII app;
    app.Main();
    return 0;
}