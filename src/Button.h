#pragma once
#include "Scene.h"
#include "ResourcesManager.h"

class Button
{
public:
    Button(SDL_FRect rect, SDL_Texture *textIdle, SDL_Texture *textHover, SDL_Texture *textPush);
    virtual ~Button();
    void HandleEvents(SDL_Event &event);
    void Render(SDL_Renderer *renderer);
    void StateReset();

protected:
    virtual void OnClicked() = 0;

private:
    enum class State
    {
        IDLE = 0,
        HOVER,
        PRESSED
    };

private:
    SDL_FRect rect;
    SDL_Texture *textIdle;
    SDL_Texture *textHover;
    SDL_Texture *textPush;
    State state = State::IDLE;
    ResourcesManager &instance = ResourcesManager::GetInstance();
};

class ButtonStart : public Button
{
public:
    ButtonStart(SDL_FRect rect, SDL_Texture *textIdle, SDL_Texture *textHover, SDL_Texture *textPush)
        : Button(rect, textIdle, textHover, textPush) {}
    ~ButtonStart() = default;

    void OnClicked() override;
};

class ButtonExit : public Button
{
public:
    ButtonExit(SDL_FRect rect, SDL_Texture *textIdle, SDL_Texture *textHover, SDL_Texture *textPush)
        : Button(rect, textIdle, textHover, textPush) {}
    ~ButtonExit() = default;

    void OnClicked() override;
};