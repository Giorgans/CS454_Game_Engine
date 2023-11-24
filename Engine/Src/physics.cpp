//
// Created by Georgios Zervos on 24/11/23.
//

#include "../Include/physics.h"
#include "../Include/sprite.h"
#include "../Include/terrain.h"
extern TileLayer *terrain;


void Physic() {
    PrepareSpriteGravityHandler(terrain->GetGrid(), SpriteManager::GetSingleton().GetDisplayList().at(0));
}
