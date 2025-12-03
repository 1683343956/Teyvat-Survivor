#include "Enemy.h"
#include <random>

Enemy::Enemy()
{
    anim_right = new Animation(instance.enemyList, 0.045f);
    rect = instance.enemyDstRect;
    imgShadow = instance.enemyShadow;
    rectShadow = instance.enemyShadowDstRect;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 999);
    enum class spawnEnemy
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    spawnEnemy spawn = spawnEnemy(dis(gen) % 4);

    float re = dis(gen) / 1000.0f;

    switch (spawn)
    {
    case spawnEnemy::UP:
        rect.x = re * (instance.WIDTH +2 *rect.w)- rect.w;
        rect.y = -rect.h;
        break;
    case spawnEnemy::DOWN:
        rect.x = re * (instance.WIDTH + 2*rect.w)- rect.w;
        rect.y = static_cast<float>(instance.HEIGHT);
        break;
    case spawnEnemy::LEFT:
        rect.x = -rect.w;
        rect.y = re * (instance.HEIGHT + 2*rect.h)- rect.h;
        break;
    case spawnEnemy::RIGHT:
        rect.x = static_cast<float>(instance.WIDTH);
        rect.y = re * (instance.HEIGHT + 2 * rect.h) - rect.h;
        break;
    }
}

Enemy::~Enemy()
{
    delete anim_right;
}

void Enemy::Update(float delta, const SDL_FRect &playerRect)
{
    Move(delta, playerRect);
    anim_right->Update(delta);
}

void Enemy::Render(SDL_Renderer *renderer)
{
    rectShadow.x = rect.x - (rectShadow.w - rect.w) / 2;
    rectShadow.y = rect.y + rect.h-30;
    SDL_RenderTexture(renderer, imgShadow, nullptr, &rectShadow);
    anim_right->Render(renderer, &rect, is_facing_left);
}

SDL_FRect Enemy::GetRect() const
{
    return rect;
}

void Enemy::SetAlive(bool alive)
{
   isAlive = alive;
}

bool Enemy::GetAlive() const
{
    return isAlive;
}

void Enemy::Move(float delta, const SDL_FRect &playerRect)
{
    const SDL_FPoint playerCenter = {playerRect.x + playerRect.w / 2, playerRect.y + playerRect.h / 2};
    SDL_FPoint enemyCenter = {rect.x + rect.w / 2, rect.y + rect.h / 2};
    SDL_FPoint direction = {playerCenter.x - enemyCenter.x, playerCenter.y - enemyCenter.y};
    double distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance != 0)
    {
        direction.x /= static_cast<float>(distance);
        direction.y /= static_cast<float>(distance);
    }
    rect.x += direction.x * PLAYER_SPEED * delta;
    rect.y += direction.y * PLAYER_SPEED * delta;

    if (direction.x < 0)
        is_facing_left = true;
    else if (direction.x > 0)
        is_facing_left = false;
}
