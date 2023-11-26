//
// Created by Georgios Zervos on 6/12/21.
//
#include "../app.h"

extern std::map<std::string,bool> inputs;
void app::Game::MainLoop() {
    while (!IsFinished())
        MainLoopIteration();
}


void app::Game::MainLoopIteration() {
    setgametime();
    Sound();
    Render();
    Input();
    ProgressAnimations();
    AI();
    Physics();
    CollisionChecking();
    UserCode();  // hook for custom code at end CommitDestructions();
    if (inputs.at("exit")) { SetDone(Done); }
}


