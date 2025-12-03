#pragma once
#include "Scene.h"

class Bullet
{
public:
    Bullet() = default;
    ~Bullet() = default;

    void Render(SDL_Renderer *renderer)
    {
        SDL_SetRenderDrawColor(renderer, 255, 155, 50, 255);
        SDL_FRect rect = {position.x - size, position.y - size, 2 * size, 2 * size};
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 200, 75, 10, 255);
        SDL_RenderRect(renderer, &rect);
    }

    SDL_FPoint GetPos()const
    {
        return position;
    }

    void SetPos(SDL_FPoint pos)
    {
        this->position = pos;
    }

private:
    SDL_FPoint position = {0, 0};
    const float size = 8;
};