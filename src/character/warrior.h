#pragma once

#include "../animation/animation.h"
#include "../object/game_object.h"
#include "../physics/rigid_body.h"
#include "character.h"

class Warrior : Character {

public:
  Warrior(Properties *props);

  void Draw() override;
  void Clean() override;
  void Update(float dt) override;

private:
  Animation *m_Animation;
  RigidBody *m_RigidBody;
};
