//
// Created by Georgios Zervos on 6/12/21.
//
#include "app.h"
void app::Game::MainLoop (void) {
    while (!IsFinished())
        MainLoopIteration();
}

void app::Game::MainLoopIteration (void) {
    Render();
    Input();
    ProgressAnimations();
    AI();
    Physics();
    CollisionChecking();
    UserCode();  // hook for custom code at end CommitDestructions();
}