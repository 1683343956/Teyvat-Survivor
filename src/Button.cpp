#include "Button.h"
#include "ResourcesManager.h"

Button::Button(SDL_FRect rect, SDL_Texture *textIdle, SDL_Texture *textHover, SDL_Texture *textPush)
{
    this->rect = rect;
    this->textIdle = textIdle;
    this->textHover = textHover;
    this->textPush = textPush;
    state = State::IDLE;
}

Button::~Button()
{
}

void Button::HandleEvents(SDL_Event &event)
{
    SDL_FPoint cursor = {event.motion.x, event.motion.y};
    switch (event.type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        if (SDL_PointInRectFloat(&cursor, &rect) && state == State::IDLE)
            state = State::HOVER;
        else if (!SDL_PointInRectFloat(&cursor, &rect) && state == State::HOVER)
            state = State::IDLE;
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (SDL_PointInRectFloat(&cursor, &rect))
            state = State::PRESSED;
        Mix_PlayChannel(-1, instance.sound, 0);
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (state == State::PRESSED)
            OnClicked();
        break;
    default:
        break;
    }
}

void Button::Render(SDL_Renderer *renderer)
{
    switch (state)
    {
    case State::IDLE:
        SDL_RenderTexture(renderer, textIdle, NULL, &rect);
        break;
    case State::HOVER:
        SDL_RenderTexture(renderer, textHover, NULL, &rect);
        break;
    case State::PRESSED:
        SDL_RenderTexture(renderer, textPush, NULL, &rect);
        break;
    }
}

void Button::StateReset()
{
    state = State::IDLE;
}

void ButtonStart::OnClicked()
{
    ResourcesManager::GetInstance().isStartGame = true;
}

void ButtonExit::OnClicked()
{
    ResourcesManager::GetInstance().isRunning = false;
}
