#include "Animation.h"

Animation::Animation(std::vector<SDL_Texture *> texture_list, float interval)
{
    this->interval = interval;
    this->texture_list = texture_list;
    idx_frame = 0;
    timer = 0;
}

Animation::~Animation()
{
}

void Animation::Update(float delta)
{
    timer += delta;
    if (timer >= interval)
    {
        timer -= interval;
        idx_frame++;
        if (idx_frame >= texture_list.size())
        {
            idx_frame = 0;
        }
    }
}

void Animation::Render(SDL_Renderer *renderer, SDL_FRect *rect, bool is_facing_left)
{
    if (is_facing_left)
        SDL_RenderTextureRotated(renderer, texture_list[idx_frame], nullptr, rect,
                                 0, nullptr, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderTexture(renderer, texture_list[idx_frame], nullptr, rect);
}
