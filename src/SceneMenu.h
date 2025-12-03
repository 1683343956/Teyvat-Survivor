#pragma once
#include "Scene.h"
#include "Button.h"

class SceneMenu : public Scene
{
public:
    SceneMenu();
    ~SceneMenu();

    void Init() override;
    void HandleEvents(SDL_Event &event) override;
    void Update(float delta) override;
    void Render(SDL_Renderer *renderer) override;
    ResourcesManager &instance = ResourcesManager::GetInstance();

    Button *buttonStart;
    Button *buttonExit;
};