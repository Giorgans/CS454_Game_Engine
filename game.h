//
// Created by Georgios Zervos on 18/11/21.
//

#ifndef CS454_SUPER_MARIO_GAME_GAME_H
#define CS454_SUPER_MARIO_GAME_GAME_H
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>


class Game{
    public:
        virtual void MainLoop();
        virtual void MainLoopIteration(){};
    Game(){

    }
};


#endif //CS454_SUPER_MARIO_GAME_GAME_H
