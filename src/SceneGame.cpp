#include "SceneGame.h"
#include <string>

SceneGame::SceneGame()
{
    player = new Player();
    bulletList = std::vector<Bullet>(12, Bullet());
    Mix_PlayMusic(instance.music, -1);
}

SceneGame::~SceneGame()
{
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroySurface(scoreSurface);
    delete player;
}

void SceneGame::Init()
{
}

void SceneGame::HandleEvents(SDL_Event &event)
{
    player->HandleEvents(event);
}

void SceneGame::Update(float delta)
{
    trySpawnEnemy();

    player->Update(delta);
    UpdateBullet();

    for (auto enemy : enemyList)
    {
        enemy->Update(delta, player->GetRect());
    }

    CheckCollisionBulletToEnemy();
    CheckCollisionPlayerToEnemy();
}

void SceneGame::Render(SDL_Renderer *renderer)
{
    SDL_RenderTexture(renderer, instance.background, &instance.backgroundSrcRect, nullptr);
    player->Render(renderer);

    for (auto bullet : bulletList)
    {
        bullet.Render(renderer);
    }

    for (auto enemy : enemyList)
    {
        enemy->Render(renderer);
    }

    RenderScore(renderer);
}

void SceneGame::UpdateBullet()
{
    SDL_FRect rect = player->GetRect();
    double radianInterval = 2 * SDL_PI_D / bulletList.size();
    double radius = 100 + 60 * sin(SDL_GetTicks() * RADIAL_SPEED);
    for (int i = 0; i < bulletList.size(); i++)
    {
        double radian = SDL_GetTicks() * TANGENT_SPEED + i * radianInterval;
        bulletList[i].SetPos({static_cast<float>(rect.x + rect.h / 2 + radius * sin(radian)),
                              static_cast<float>(rect.y + rect.h / 2 + radius * cos(radian))});
    }
}

void SceneGame::trySpawnEnemy()
{
    const int INTERVAL = 4;
    static int count = 0;
    if (count++ % INTERVAL == 0)
    {
        enemyList.push_back(new Enemy());
    }
}

void SceneGame::CheckCollisionBulletToEnemy()
{
    for (auto enemy : enemyList)
    {
        for (auto bullet : bulletList)
        {
            SDL_FPoint bulletPos = bullet.GetPos();
            SDL_FRect enemyRect = enemy->GetRect();
            if (SDL_PointInRectFloat(&bulletPos, &enemyRect))
            {
                enemy->SetAlive(false);
                Mix_PlayChannel(-1, instance.sound, 0);
                score += 10;
                break;
            }
        }
    }

    for (int i = 0; i < enemyList.size(); i++)
    {
        if (!enemyList[i]->GetAlive())
        {
            std::swap(enemyList[i], enemyList.back());
            delete enemyList.back();
            enemyList.pop_back();
        }
    }
}

void SceneGame::CheckCollisionPlayerToEnemy()
{
    for (auto enemy : enemyList)
    {
        SDL_FPoint enemyPos = {enemy->GetRect().x + enemy->GetRect().w / 2,
                               enemy->GetRect().y + enemy->GetRect().h / 2};
        SDL_FRect playerRect = player->GetRect();
        if (SDL_PointInRectFloat(&enemyPos, &playerRect))
        {
            Mix_HaltMusic();
            SDL_Delay(2000);

            instance.isStartGame = false;
            break;
        }
    }
}

void SceneGame::RenderScore(SDL_Renderer *renderer)
{
    SDL_Color textColor = {255, 0, 0, 255};

    std::string scoreText = std::to_string(score);
    if (scoreText.size() < 6)
    {
        std::string padding(6 - scoreText.size(), ' ');
        scoreText = "分数:" + padding + scoreText;
    }
    else
    {
        scoreText = "分数:" + scoreText;
    }
    scoreSurface = TTF_RenderText_Solid(instance.font, scoreText.c_str(), scoreText.size(), textColor);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FRect scoreRect = {10, 10,
                           static_cast<float>(scoreSurface->w) , static_cast<float>(scoreSurface->h) };
    SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);
}
