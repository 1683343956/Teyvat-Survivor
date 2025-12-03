#pragma once
#include "Scene.h"
#include <vector>

class Animation
{
public:
    Animation(std::vector<SDL_Texture *> texture_list, float interval);
    ~Animation();

    void Update(float delta);
    void Render(SDL_Renderer* renderer, SDL_FRect* rect,bool is_facing_left);

private:
    std::vector<SDL_Texture*> texture_list;
    float interval;
    float timer;
    int idx_frame;
};

