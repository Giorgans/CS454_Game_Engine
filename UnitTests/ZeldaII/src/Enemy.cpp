#include "Enemy.h"

Enemy::Enemy(Sprite* sprite, int health) : sprite(sprite), health(health) {}

void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        sprite->SetVisibility(false);
    }
}
