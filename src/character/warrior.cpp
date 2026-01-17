
#include "warrior.h"
#include "../input/input.h"
#include <SDL2/SDL.h>

Warrior::Warrior(Properties *props) : Character(props) {
  m_Animation = new Animation();
  m_Animation->SetProps(m_TextureID, 0, 7, 60);
  m_RigidBody = new RigidBody();
};

void Warrior::Draw() {
  m_Animation->Draw(m_Transform->x, m_Transform->y, m_Width, m_Height);
};

void Warrior::Clean() {

};

void Warrior::Update(float dt) {
  m_RigidBody->Update(0.1);
  m_RigidBody->UnsetForce();
  m_Animation->SetProps("player_idle", 0, 5, 100);

  if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
    m_Animation->SetProps("player_run", 0, 7, 100);
    m_RigidBody->ApplyForce(Vec2(100));
  }
  if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
    m_Animation->SetProps("player_run", 0, 7, 100, SDL_FLIP_HORIZONTAL);
    m_RigidBody->ApplyForce(Vec2(-100));
  }

  m_Transform->x += m_RigidBody->GetPosition().x;
  // m_Transform->y = m_RigidBody->GetPosition().y;
  m_Animation->Update();
};
