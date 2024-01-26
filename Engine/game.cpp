#include "../app.h"

extern std::map<std::string,bool> inputs;
void app::Game::MainLoop() {
    while (!IsFinished())
        MainLoopIteration();
}


void app::Game::MainLoopIteration() {
    SetGameTime();
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


