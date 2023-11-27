//
// Created by Georgios Zervos on 27/11/23.
//

#include "../../../Engine/Include/sprite.h"



/***************************************
 *  Creating Sprites Functions        *
 **************************************/

void createLink() {
    Sprite *Link = new Sprite(LINK_STARTING_POINT_X,LINK_STARTING_POINT_Y,AnimationFilmHolder::GetHolder().Load(WalkingRight),"Link");
    Link->SetVisibility(true);
    Link->SetZorder(1);
    SpriteManager::GetSingleton().Add(Link);
}

