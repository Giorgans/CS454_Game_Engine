//
// Created by Georgios Zervos on 15/12/21.
//

#ifndef CS454_GAME_ENGINE_INPUT_H
#define CS454_GAME_ENGINE_INPUT_H
#include "../Include/rendering.h"
#include "sound.h"
#include <map>

extern TileLayer *background,*terrain;

void input(void);
void InitializeInputs();

#endif //CS454_GAME_ENGINE_INPUT_H
