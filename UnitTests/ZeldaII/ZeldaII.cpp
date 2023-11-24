//
// Created by Georgios Zervos on 24/11/23.
//
#include "ZeldaII.h"
#include "../../Engine/Include/sprite.h"

void createLink() {
    Sprite *Link = new Sprite(LINK_STARTING_POINT_X,LINK_STARTING_POINT_Y,AnimationFilmHolder::GetHolder().Load(WalkingRight),"Link");
    Link->SetVisibility(true);
    Link->SetZorder(1);
    SpriteManager::GetSingleton().Add(Link);
}