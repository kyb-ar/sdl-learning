#include "core/engine.h"
#include "timer/timer.h"

int main(int argc, char *args[]) {
  Engine::GetInstance()->Init();
  while (Engine::GetInstance()->IsRunning()) {
    Engine::GetInstance()->Events();
    Engine::GetInstance()->Update();
    Engine::GetInstance()->Render();
    Timer::GetInstance()->Tick();
  }

  Engine::GetInstance()->Clean();
  Engine::GetInstance()->Quit();
}
