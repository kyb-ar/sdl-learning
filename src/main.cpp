// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include <stdio.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite {
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_TOTAL = 4,
};

SDL_Rect gSpriteClips[TOTAL_BUTTONS];

class LTexture {
public:
  // Initializes the variables
  LTexture();

  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(std::string path);

  // Creates image from font string
  bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

  // Deallocates texture
  void free();

  // Renders texture at given point
  void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
              SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Sets the texture color modulation
  void setColor(Uint8 r, Uint8 g, Uint8 b);

  // Sets the texture blend mode
  void setBlendMode(SDL_BlendMode blending);

  // Set Alpha Modulation
  void setAlpha(Uint8 alpha);

  // Gets image dimensions
  int getWidth();
  int getHeight();

private:
  // The actual hardware texture.
  SDL_Texture *mTexture;

  // Image Dimensions
  int mWidth;
  int mHeight;
};

// The window we'll be rendering to.
SDL_Window *gWindow = NULL;

// The window rendere
SDL_Renderer *gRenderer = NULL;

TTF_Font *gFont = NULL;
LTexture gTextTexture;

LTexture::LTexture() {
  // Initialize
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
  // Deallocate
  free();
}

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
  SDL_SetTextureColorMod(mTexture, r, g, b);
}

bool LTexture::loadFromRenderedText(std::string text, SDL_Color textColor) {
  free();

  SDL_Surface *textSurface =
      TTF_RenderText_Solid(gFont, text.c_str(), textColor);

  // Render text surface
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    return false;
  }

  mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

  SDL_FreeSurface(textSurface);

  if (mTexture == NULL) {
    printf("Unable to create texture from rendered text! SDL Error: %s\n",
           SDL_GetError());
    return false;
  }

  mWidth = textSurface->w;
  mHeight = textSurface->h;

  return true;
}

bool LTexture::loadFromFile(std::string path) {
  // Get rid of preexisting texture
  free();

  // The final texture
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
    return false;
  }

  SDL_SetColorKey(loadedSurface, SDL_TRUE,
                  SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

  // Create texture from surface pixels
  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
  if (newTexture == NULL) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
    SDL_FreeSurface(loadedSurface);
    return false;
  }

  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;
  mTexture = newTexture;

  SDL_FreeSurface(loadedSurface);
  return true;
}

void LTexture::free() {
  if (mTexture == NULL) {
    return;
  }

  SDL_DestroyTexture(mTexture);
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle,
                      SDL_Point *center, SDL_RendererFlip flip) {
  // Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
};

void LTexture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

class LButton {
public:
  LButton();

  void setPosition(int x, int y);

  void handleEvent(SDL_Event *e);

  void render();

private:
  SDL_Point mPosition;

  // Currently used global sprite
  LButtonSprite mCurrentSprite;
};

LButton::LButton() {
  mPosition.x = 0;
  mPosition.y = 0;

  mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
};

void LButton::setPosition(int x, int y) {
  mPosition.x = x;
  mPosition.y = y;
};

void LButton::handleEvent(SDL_Event *e) {
  if (e->type != SDL_MOUSEMOTION && e->type != SDL_MOUSEBUTTONDOWN &&
      e->type != SDL_MOUSEBUTTONUP) {
    return;
  }
  // Get mouse position
  int x, y;
  SDL_GetMouseState(&x, &y);

  if (x < mPosition.x) {
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    return;
  } else if (x > mPosition.x + BUTTON_WIDTH) {
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    return;

  } else if (y < mPosition.y) {
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    return;

  } else if (y > mPosition.y + BUTTON_HEIGHT) {
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    return;
  }

  switch (e->type) {
  case SDL_MOUSEMOTION:
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
    break;
  case SDL_MOUSEBUTTONDOWN:
    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
    break;
  case SDL_MOUSEBUTTONUP:
    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
    break;
  }
};

LButton gButtons[TOTAL_BUTTONS];
LTexture gButtonSpriteSheetTexture;

void LButton::render() {
  gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y,
                                   &gSpriteClips[mCurrentSprite]);
};

bool loadMedia() {

  if (!gButtonSpriteSheetTexture.loadFromFile("17_mouse_events/button.png")) {
    printf("Failed to load Foo texture image!\n");
    return false;
  }

  for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++) {
    gSpriteClips[i].x = 0;
    gSpriteClips[i].y = i * 200;
    gSpriteClips[i].w = BUTTON_WIDTH;
    gSpriteClips[i].h = BUTTON_HEIGHT;
  }

  gButtons[0].setPosition(0, 0);
  gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
  gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
  gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH,
                          SCREEN_HEIGHT - BUTTON_HEIGHT);
  return true;
}

void close() {
  // Free loaded images
  gButtonSpriteSheetTexture.free();

  gSpriteClips[0].x = 0;
  gSpriteClips[0].y = 0;
  gSpriteClips[0].w = 64;
  gSpriteClips[0].h = 205;

  gSpriteClips[1].x = 64;
  gSpriteClips[1].y = 0;
  gSpriteClips[1].w = 64;
  gSpriteClips[1].h = 205;

  gSpriteClips[2].x = 128;
  gSpriteClips[2].y = 0;
  gSpriteClips[2].w = 64;
  gSpriteClips[2].h = 205;

  gSpriteClips[3].x = 192;
  gSpriteClips[3].y = 0;
  gSpriteClips[3].w = 64;
  gSpriteClips[3].h = 205;

  // Free loaded images
  gTextTexture.free();

  TTF_CloseFont(gFont);
  gFont = NULL;

  // Destroy Window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL substems.
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char *args[]) {
  gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    return 1;
  }

  // Create rendere for window
  gRenderer = SDL_CreateRenderer(
      gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (gRenderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  // Initialze PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
           IMG_GetError());
  }

  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
  }

  // While application is running
  bool quit = false;
  SDL_Event e;

  if (!loadMedia()) {
    return 1;
  }

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      for (int i = 0; i < TOTAL_BUTTONS; i++) {
        gButtons[i].handleEvent(&e);
      }
    }

    // Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
      gButtons[i].render();
    }

    SDL_RenderPresent(gRenderer);
  }
  close();
}
