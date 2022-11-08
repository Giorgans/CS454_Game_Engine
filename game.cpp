//
// Created by Georgios Zervos on 6/12/21.
//
#include "app.h"
extern bool isDone;
void app::Game::MainLoop() {
    while (!IsFinished())
        MainLoopIteration();
}

// allagi

void app::Game::MainLoopIteration() {
    Render();
    Input();
    ProgressAnimations();
    AI();
    Physics();
    CollisionChecking();
    UserCode();  // hook for custom code at end CommitDestructions();
    if (isDone) { SetDone(Done); }
}