#pragma once

#include "../physics/vector_2d.h"
#include <SDL2/SDL.h>
#include <string>

class Vec2 {

public:
  Vec2(float x = 0, float y = 0) : x(x), y(y) {};

  float x, y;

  inline Vec2 operator+(const Vec2 &v2) const {
    return Vec2(x + v2.x, y + v2.y);
  }

  inline Vec2 operator-(const Vec2 &v2) const {
    return Vec2(x - v2.x, y - v2.y);
  }

  inline Vec2 operator*(const float scalar) const {
    return Vec2(x * scalar, y * scalar);
  }

  void Log(std::string msg = "") {
    SDL_Log("%s(X,Y) = (%f, %f)", msg.c_str(), x, y);
  }

private:
};
