#pragma once
#include "Scene.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class SceneGame : public Scene
{
public:
    SceneGame();
    ~SceneGame();

    void Init() override;
    void HandleEvents(SDL_Event &event) override;
    void Update(float delta) override;
    void Render(SDL_Renderer *renderer) override;

private:
    void UpdateBullet();
    void trySpawnEnemy();

    void CheckCollisionBulletToEnemy();
    void CheckCollisionPlayerToEnemy();

    void RenderScore(SDL_Renderer *renderer);

private:
    ResourcesManager &instance = ResourcesManager::GetInstance();
    Player *player;
    std::vector<Bullet> bulletList;
    std::vector<Enemy *> enemyList;
    const double RADIAL_SPEED = 0.0045;
    const double TANGENT_SPEED = 0.0055;
    int score = 0;

    SDL_Surface *scoreSurface;
    SDL_Texture *scoreTexture;
};