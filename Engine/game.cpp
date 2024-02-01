#include "../app.h"


void app::Game::MainLoop() {
    while (!IsFinished())
        MainLoopIteration();
}

void app::Game::MainLoopIteration() {
        SetGameTime();
        Render();
        ProcessInput();
        Input();
        if (!IsPaused()) {
            Sound();
            ProgressAnimations();
            AI();
            Physics();
            CollisionChecking();
        }
        UserCode(); // Custom code hook
        CommitDestructions();
        if (inputs["exit"]) {
            SetDone(Done);
        }
    }

void app::Game::HandleTogglePauseResume () {
    if (IsPaused())
        Resume();
    else
        Pause(GetGameTime());
}

void app::Game::ProcessInput() {
    if (inputs["P"]) {
        HandleTogglePauseResume();
    }
}
