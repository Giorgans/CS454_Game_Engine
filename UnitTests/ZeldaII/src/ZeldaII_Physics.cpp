#include "../ZeldaII.h"
#include "../../../Engine/Include/sprite.h"
#include "../../../Engine/Include/rendering.h"

void ZeldaII_Physics() {
    CollisionChecker::GetSingleton().Check();
}