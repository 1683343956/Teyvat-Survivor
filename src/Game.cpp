#include "Game.h"
#include "ResourcesManager.h"
Game::Game()
{  
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
        instance.isRunning = false;
    }
    // 初始化音频
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init Error: %s", SDL_GetError());
        instance.isRunning = false;
    }
    if (!Mix_OpenAudio(0, NULL))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s", SDL_GetError());
        instance.isRunning = false;
    }
    Mix_AllocateChannels(32);            // 分配16个音频通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 32);  // 设置音效音量
    // TTF初始化
    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init Error: %s", SDL_GetError());
        instance.isRunning = false;
    }
    // 创建窗口和渲染器
    SDL_CreateWindowAndRenderer(u8"提瓦特幸存者", instance.WIDTH, instance.HEIGHT, NULL, &window, &renderer);
    if (!window || !renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
        instance.isRunning = false;
    }
    instance.loadResources(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    tick = 1e9 / FPS;
    currentScene = new SceneMenu();
}

Game::~Game()
{
    delete currentScene;
    instance.destroyResources();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Init()
{
}

void Game::HandleEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            instance.isRunning = false;
        }
        currentScene->HandleEvents(event);
    }
}

void Game::Update()
{
    static float delta = 0.0f;
    static Uint64 lastFrame = SDL_GetTicksNS();
    delta = static_cast<float>((SDL_GetTicksNS() - lastFrame) / 1e9);
    lastFrame = SDL_GetTicksNS();
    currentScene->Update(delta);
    if(instance.isStartGame&&!isGame)
    {
        delete currentScene;
        currentScene = new SceneGame();
        isGame = true;
    }
    else if(!instance.isStartGame&&isGame)
    {
        delete currentScene;
        currentScene = new SceneMenu();
        isGame = false;
    }
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    currentScene->Render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::Run()
{
    while (instance.isRunning)
    {
        auto start = SDL_GetTicksNS();
        HandleEvents();
        Update();
        Render();
        auto delta = tick - SDL_GetTicksNS() + start;
        if (delta > 0)
        {
            SDL_DelayNS(static_cast<Uint64>(delta));
        }
    }
}
