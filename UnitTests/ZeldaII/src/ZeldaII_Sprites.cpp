
#include "../../../Engine/Include/sprite.h"



/***************************************
 *  Creating Sprites Functions        *
 *************************************/

void createTittleScreen(){
    auto *TitleScn = new Sprite(ZELDA_STARTING_LEVEL_STARTING_POINT_X,ZELDA_STARTING_LEVEL_STARTING_POINT_Y,AnimationFilmHolder::GetHolder().Load(TitleScreen),"TitleScreen");
    TitleScn->SetFrame(0);
    TitleScn->SetVisibility(true);
    TitleScn->SetZorder(1);
    SpriteManager::GetSingleton().Add(TitleScn);

}

void createLink() {
    auto *Link = new Sprite(LINK_STARTING_POINT_X,LINK_STARTING_POINT_Y,AnimationFilmHolder::GetHolder().Load(WalkingRight),"Link");
    Link->SetFrame(0);
    Link->SetVisibility(true);
    Link->SetZorder(0);
    SpriteManager::GetSingleton().Add(Link);
}

