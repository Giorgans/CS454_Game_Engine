//
// Created by Georgios Zervos on 17/11/21.
//

#ifndef CS454_SUPER_MARIO_GAME_APP_H
#define CS454_SUPER_MARIO_GAME_APP_H
#include <allegro5/allegro.h>
#include "game.h"
#include <iostream>
namespace app {
    class App {
    protected:
        Game game;

    public:
        virtual void	Initialise (void) = 0;
        virtual void	Load (void) = 0;
        virtual void	Run (void) {  game.MainLoop();  }
        virtual void	RunIteration (void)
        {  game.MainLoopIteration();  }
        Game&			GetGame (void) { return game; }
        const Game&		GetGame (void) const { return game; }
        virtual void	Clear (void) = 0;
        void Main (void) {
            Initialise();
            Load();
            Run();
            Clear();
        }
    };
}


#endif //CS454_SUPER_MARIO_GAME_APP_H
