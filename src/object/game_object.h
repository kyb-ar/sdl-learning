#pragma once

#include "../physics/transform.h"
#include "object.h"
#include <SDL2/SDL.h>

struct Properties {
public:
  Properties(std::string textureID, int x_, int y_, float width, float height,
             SDL_RendererFlip flip = SDL_FLIP_NONE) {
    Width = width;
    Height = height;
    x = x_;
    y = y_;
    TextureID = textureID;
    Flip = flip;
  };

  int Width, Height;
  float x, y;
  std::string TextureID;
  SDL_RendererFlip Flip;
};

class GameObject : public IObject {

public:
  GameObject(Properties *props) {
    m_Width = props->Width;
    m_Height = props->Height;
    m_TextureID = props->TextureID;
    m_Flip = props->Flip;
    m_Transform = new Transform(props->x, props->y);
  };

  void Draw() override{};
  void Update() override{};
  void Clean() override{};

protected:
  Transform *m_Transform;
  int m_Width, m_Height;
  std::string m_TextureID;
  SDL_RendererFlip m_Flip;

private:
};
