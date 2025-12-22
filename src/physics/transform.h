#pragma once

#include "vector_2d.h"

class Transform {

public:
  Transform(float x = 0, float y = 0) : x(x), y(y){};
  float x, y;

  void Log(std::string msg = "") {
    SDL_Log("%s(X,Y) = (%f, %f)", msg.c_str(), x, y);
  }

  inline void TranslateX(float x) { x += x; };
  inline void TranslateY(float y) { y += y; };
  inline void Translate(Vec2 *v) {
    x += v->x;
    y += v->y;
  };
};
