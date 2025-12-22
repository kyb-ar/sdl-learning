#include "core/engine.h"

int main(int argc, char *args[]) {
  Engine::GetInstance()->Init();
  while (Engine::GetInstance()->IsRunning()) {
    Engine::GetInstance()->Events();
    Engine::GetInstance()->Update();
    Engine::GetInstance()->Render();
  }

  Engine::GetInstance()->Clean();
  Engine::GetInstance()->Quit();
}
