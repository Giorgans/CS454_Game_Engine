#ifndef CS454_SUPER_MARIO_GAME_ENEMY_H
#define CS454_SUPER_MARIO_GAME_ENEMY_H

#include "../../../Engine/Include/sprite.h"

class Enemy {
public:
    Sprite* sprite;
    int health;

    Enemy(Sprite* sprite, int health);
    void TakeDamage(int damage);
};

#endif //CS454_SUPER_MARIO_GAME_ENEMY_H
