#pragma once

#include "../object/game_object.h"
#include "character.h"

class Warrior : Character {

public:
  Warrior(Properties *props) : Character(props) {
    m_Row = 0;
    m_Frame = 0;
    m_FrameCount = 6;
    m_AnimSpeed = 60;
  };

  void Draw() override;
  void Clean() override;
  void Update(float dt) override;

private:
  int m_Row, m_Frame, m_FrameCount, m_AnimSpeed;
};
