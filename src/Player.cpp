#include "Player.h"

Player::Player()
{
    anim_right = new Animation(instance.playerList, 0.045f);
    rect = instance.playDstRect;
    imgShadow = instance.playerShadow;
    rectShadow = instance.playerShadowDstRect;
}

Player::~Player()
{
    delete anim_right;
}

void Player::HandleEvents(SDL_Event &event)
{
    switch (event.key.type)
    {
    case SDL_EVENT_KEY_DOWN:
        switch (event.key.key)
        {
        case SDLK_RIGHT:
        case SDLK_D:
            is_moving_right = true;
            break;
        case SDLK_LEFT:
        case SDLK_A:
            is_moving_left = true;
            break;
        case SDLK_UP:
        case SDLK_W:
            is_moving_up = true;
            break;
        case SDLK_DOWN:
        case SDLK_S:
            is_moving_down = true;
            break;
        default:
            break;
        }
        break;
    case SDL_EVENT_KEY_UP:
        switch (event.key.key)
        {
        case SDLK_RIGHT:
        case SDLK_D:
            is_moving_right = false;
            break;
        case SDLK_LEFT:
        case SDLK_A:
            is_moving_left = false;
            break;
        case SDLK_UP:
        case SDLK_W:
            is_moving_up = false;
            break;
        case SDLK_DOWN:
        case SDLK_S:
            is_moving_down = false;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Player::Update(float delta)
{
    Move(delta);
    anim_right->Update(delta);
}

void Player::Render(SDL_Renderer *renderer)
{
    rectShadow.x = rect.x - (rectShadow.w - rect.w) / 2 + (is_facing_left ? 5 : -5);
    rectShadow.y = rect.y + rect.h - 5;
    SDL_RenderTexture(renderer, imgShadow, nullptr, &rectShadow);
    anim_right->Render(renderer, &rect, is_facing_left);
}

SDL_FRect Player::GetRect() const
{
    return rect;
}

void Player::Move(float delta)
{
    int dir_x = is_moving_right - is_moving_left;
    int dir_y = is_moving_down - is_moving_up;
    double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (len_dir != 0)
    {
        rect.x += static_cast<float>(dir_x * delta * PLAYER_SPEED / len_dir);
        rect.y += static_cast<float>(dir_y * delta * PLAYER_SPEED / len_dir);
    }

    if (rect.x < 0)
        rect.x = 0;
    if (rect.y < 0)
        rect.y = 0;
    if (rect.x + rect.w > instance.WIDTH)
        rect.x = instance.WIDTH - rect.w;
    if (rect.y + rect.h > instance.HEIGHT)
        rect.y = instance.HEIGHT - rect.h;

    if (dir_x > 0)
        is_facing_left = false;
    else if (dir_x < 0)
        is_facing_left = true;
}
