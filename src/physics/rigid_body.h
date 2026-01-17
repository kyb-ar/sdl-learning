#pragma once

#include "vector_2d.h"
#include <SDL2/SDL.h>

#define UNIT_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody {

public:
  RigidBody() {
    m_Mass = UNIT_MASS;
    m_Gravity = GRAVITY;
  };

  // Setters
  inline void SetMass(float mass) { m_Mass = mass; };
  inline void SetGravity(float gravity) { m_Gravity = gravity; };

  inline void ApplyForce(Vec2 F) { m_Force = F; };
  inline void UnsetForce() { m_Force = Vec2(); };

  inline void ApplyFriction(Vec2 F) { m_Friction = F; };
  inline void UnsetFriction() { m_Friction = Vec2(); };

  // Getters
  inline float GetMass() { return m_Mass; };
  inline Vec2 GetPosition() { return m_Position; };
  inline Vec2 GetVelocity() { return m_Velocity; };
  inline Vec2 GetAcceleration() { return m_Acceleration; };

  void Update(float dt) {
    m_Acceleration.x = (m_Force.x + m_Friction.x) / m_Mass;
    m_Acceleration.y = m_Gravity + m_Force.y / m_Mass;
    m_Velocity = (m_Acceleration * dt);
    m_Position = (m_Velocity * dt);
  };

private:
  float m_Mass, m_Gravity;

  Vec2 m_Force;
  Vec2 m_Friction;

  Vec2 m_Position;
  Vec2 m_Velocity;
  Vec2 m_Acceleration;
};
