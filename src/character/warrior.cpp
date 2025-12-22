
#include "warrior.h"
#include "../graphics/texture_manager.h"
#include <SDL2/SDL.h>

void Warrior::Draw() {
  TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->x,
                                           m_Transform->y, m_Width, m_Height,
                                           m_Row, m_Frame);
};

void Warrior::Clean(){

};

void Warrior::Update(float dt) {
  m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
};
