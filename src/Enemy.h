#pragma once
#include "Animation.h"
#include "ResourcesManager.h"

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Update(float delta, const SDL_FRect &playerRect);
    void Render(SDL_Renderer *renderer);
    SDL_FRect GetRect() const;
    void SetAlive(bool alive);
    bool GetAlive() const;


private:
    void Enemy::Move(float delta, const SDL_FRect &playerRect);

private:
    ResourcesManager &instance = ResourcesManager::GetInstance();
    Animation *anim_right;
    SDL_FRect rect;
    SDL_Texture *imgShadow;
    SDL_FRect rectShadow;
    const int PLAYER_SPEED = 150;
    bool is_facing_left = false;
    bool isAlive = true;
};