#pragma once
#include "Scene.h"
#include <vector>

class ResourcesManager
{
public:
    ~ResourcesManager();
    void loadResources(SDL_Renderer *renderer);
    void destroyResources();
    static ResourcesManager &GetInstance();

    bool isRunning=true;
    bool isStartGame=false;

    const int WIDTH = 1280;
    const int HEIGHT = 720;

    SDL_Texture *menu;
    SDL_FRect menuSrcRect;

    SDL_Texture *startIdle;
    SDL_Texture *startHover;
    SDL_Texture *startPush;
    
    SDL_Texture *exitIdle;
    SDL_Texture *exitHover;
    SDL_Texture *exitPush;
    SDL_FRect buttonRect;

    SDL_Texture *background;
    SDL_FRect backgroundSrcRect;

    std::vector<SDL_Texture *> playerList;
    SDL_FRect playDstRect;

    SDL_Texture *playerShadow;
    SDL_FRect playerShadowDstRect;

    std::vector<SDL_Texture *> enemyList;
    SDL_FRect enemyDstRect;

    SDL_Texture *enemyShadow;
    SDL_FRect enemyShadowDstRect;

    Mix_Music *music;
    Mix_Chunk *sound;
    TTF_Font *font;
private:
    ResourcesManager();
};