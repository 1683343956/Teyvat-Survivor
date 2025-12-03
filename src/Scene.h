#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "ResourcesManager.h"

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Init() = 0;
    virtual void HandleEvents(SDL_Event &event) = 0;
    virtual void Update(float delta) = 0;
    virtual void Render(SDL_Renderer *renderer) = 0;
};