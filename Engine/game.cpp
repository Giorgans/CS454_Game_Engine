#include "../app.h"

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


