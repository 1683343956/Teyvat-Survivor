#include "ResourcesManager.h"
#include <string>
ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
}

void ResourcesManager::loadResources(SDL_Renderer *renderer)
{
    menu = IMG_LoadTexture(renderer, "img/menu.png");
    SDL_GetTextureSize(menu, &menuSrcRect.w, &menuSrcRect.h);
    menuSrcRect.x = (menuSrcRect.w - WIDTH) / 2;
    menuSrcRect.y = (menuSrcRect.h - HEIGHT) / 2;
    menuSrcRect.w = static_cast<float>(WIDTH);
    menuSrcRect.h = static_cast<float>(HEIGHT);

    startIdle = IMG_LoadTexture(renderer, "img/ui_start_idle.png");
    startHover = IMG_LoadTexture(renderer, "img/ui_start_hovered.png");
    startPush = IMG_LoadTexture(renderer, "img/ui_start_pushed.png");
    exitIdle = IMG_LoadTexture(renderer, "img/ui_quit_idle.png");
    exitHover = IMG_LoadTexture(renderer, "img/ui_quit_hovered.png");
    exitPush = IMG_LoadTexture(renderer, "img/ui_quit_pushed.png");
    SDL_GetTextureSize(startIdle, &buttonRect.w, &buttonRect.h);
    buttonRect.x = (WIDTH - buttonRect.w) / 2;

    background = IMG_LoadTexture(renderer, "img/background.png");
    SDL_GetTextureSize(background, &backgroundSrcRect.w, &backgroundSrcRect.h);
    backgroundSrcRect.x = (backgroundSrcRect.w - WIDTH) / 2;
    backgroundSrcRect.y = (backgroundSrcRect.h - HEIGHT) / 2;
    backgroundSrcRect.w = static_cast<float>(WIDTH);
    backgroundSrcRect.h = static_cast<float>(HEIGHT);

    for (int i = 0; i < 6; i++)
    {
        std::string path = "img/player_right_" + std::to_string(i) + ".png";
        SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
        playerList.push_back(texture);
    }
    SDL_GetTextureSize(playerList[0], &playDstRect.w, &playDstRect.h);
    playDstRect.x = (WIDTH - playDstRect.w) / 2;
    playDstRect.y = (HEIGHT - playDstRect.h) / 2;

    playerShadow = IMG_LoadTexture(renderer, "img/shadow_player.png");
    SDL_GetTextureSize(playerShadow, &playerShadowDstRect.w, &playerShadowDstRect.h);
    playerShadowDstRect.x=0;
    playerShadowDstRect.y=0;

    for (int i = 0; i < 6; i++)
    {
        std::string path = "img/enemy_right_" + std::to_string(i) + ".png";
        SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
        enemyList.push_back(texture);
    }
    SDL_GetTextureSize(enemyList[0], &enemyDstRect.w, &enemyDstRect.h);
    enemyDstRect.x = 0;
    enemyDstRect.y = 0;

    enemyShadow = IMG_LoadTexture(renderer, "img/shadow_enemy.png");
    SDL_GetTextureSize(enemyShadow, &enemyShadowDstRect.w, &enemyShadowDstRect.h);

    music=Mix_LoadMUS("mus/bgm.mp3");
    sound=Mix_LoadWAV("mus/hit.wav");

    font = TTF_OpenFont("font/VonwaonBitmap-16px.ttf", 20);
}   

void ResourcesManager::destroyResources()
{
    TTF_CloseFont(font);

    Mix_FreeChunk(sound);
    Mix_FreeMusic(music);

    for(auto texture : enemyList)
        SDL_DestroyTexture(texture);
    enemyList.clear();
    SDL_DestroyTexture(enemyShadow);

    SDL_DestroyTexture(playerShadow);
    for (auto texture : playerList)
        SDL_DestroyTexture(texture);
    playerList.clear();
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(startIdle);
    SDL_DestroyTexture(startHover);
    SDL_DestroyTexture(startPush);
    SDL_DestroyTexture(exitIdle);
    SDL_DestroyTexture(exitHover);
    SDL_DestroyTexture(exitPush);
    delete this;
}

ResourcesManager &ResourcesManager::GetInstance()
{
    static ResourcesManager *instance = new ResourcesManager();
    return *instance;
}
