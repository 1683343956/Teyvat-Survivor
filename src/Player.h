#pragma once
#include "Animation.h"
#include "ResourcesManager.h"

    class Player
{
public:
    Player();
    ~Player();
    void HandleEvents(SDL_Event &event);
    void Update(float delta);
    void Render(SDL_Renderer *renderer);

    SDL_FRect GetRect() const;

public:
    const int PLAYER_WIDTH = 80;
    const int PLAYER_HEIGHT = 80;

private:
    void Move(float delta);

private:
    ResourcesManager &instance = ResourcesManager::GetInstance();
    Animation *anim_right;
    SDL_FRect rect;
    SDL_Texture *imgShadow;
    SDL_FRect rectShadow;
    const int PLAYER_SPEED = 200;
    bool is_moving_left = false;
    bool is_moving_right = false;
    bool is_moving_up = false;
    bool is_moving_down = false;
    bool is_facing_left = false;
};