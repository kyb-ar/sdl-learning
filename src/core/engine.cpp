#include "engine.h"
#include "../character/warrior.h"
#include "../graphics/texture_manager.h"
#include "../input/input.h"
#include "../object/game_object.h"

#include <SDL2/SDL_image.h>

Engine *Engine::s_Instance = nullptr;
Warrior *player = nullptr;

bool Engine::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return false;
  }
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
    SDL_Log("Failed to initialize IMG: %s", IMG_GetError());
    return false;
  }

  m_Window =
      SDL_CreateWindow("Cool Engine SDL Learning", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (m_Window == nullptr) {
    SDL_Log("Failed to create Window: %s", SDL_GetError());
    return false;
  }

  m_Renderer = SDL_CreateRenderer(
      m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_Renderer == nullptr) {
    SDL_Log("Failed to create Renderer: %s", SDL_GetError());
  }
  TextureManager::GetInstance()->LoadTexture("tree", "assets/tree.png");
  TextureManager::GetInstance()->LoadTexture("player_idle", "assets/idle.png");
  TextureManager::GetInstance()->LoadTexture("player_run", "assets/run.png");
  player = new Warrior(new Properties("player_run", 100, 480, 136, 96));

  return m_IsRunning = true;
};

bool Engine::Clean() {
  TextureManager::GetInstance()->Clean();
  SDL_DestroyRenderer(m_Renderer);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
  IMG_Quit();
  return true;
};

void Engine::Quit() { m_IsRunning = false; };

void Engine::Update() {
  if (player != nullptr) {
    player->Update(0);
  }
};

void Engine::Render() {
  SDL_SetRenderDrawColor(m_Renderer, 200, 255, 200, 255);
  SDL_RenderClear(m_Renderer);

  TextureManager::GetInstance()->Draw("tree", 100, 100, 347, 465);
  Properties props("test", 0, 0, 10, 10);
  GameObject obj(&props);
  player->Draw();

  SDL_RenderPresent(m_Renderer);
};

void Engine::Events() { Input::GetInstance()->Listen(); };
