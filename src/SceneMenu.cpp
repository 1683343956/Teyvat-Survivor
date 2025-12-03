#include "SceneMenu.h"
#include "Button.h"

SceneMenu::SceneMenu()
{
    instance.buttonRect.y = 380;
    buttonStart = new ButtonStart(instance.buttonRect, instance.startIdle,
                                  instance.startHover, instance.startPush);
    instance.buttonRect.y += 100;
    buttonExit = new ButtonExit(instance.buttonRect, instance.exitIdle,
                                instance.exitHover, instance.exitPush);
}

SceneMenu::~SceneMenu()
{
    delete buttonStart;
    delete buttonExit;
}

void SceneMenu::Init()
{
}

void SceneMenu::HandleEvents(SDL_Event &event)
{
    buttonStart->HandleEvents(event);
    buttonExit->HandleEvents(event);
}

void SceneMenu::Update(float delta)
{
        
}

void SceneMenu::Render(SDL_Renderer *renderer)
{
    SDL_RenderTexture(renderer, instance.menu, &instance.menuSrcRect, nullptr);
    buttonStart->Render(renderer);
    buttonExit->Render(renderer);
}
