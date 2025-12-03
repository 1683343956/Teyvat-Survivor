#pragma once
#include "SceneMenu.h"
#include "SceneGame.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void HandleEvents();
    void Update();
    void Render();
    void Run();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    Scene *currentScene= nullptr;
    double tick;
    ResourcesManager &instance = ResourcesManager::GetInstance();
private:
    const int FPS = 144;
    bool isGame = false;
};
