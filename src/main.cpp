// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include <stdio.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to.
SDL_Window *gWindow = NULL;

// The window rendere
SDL_Renderer *gRenderer = NULL;

class LTexture {
public:
  // Initializes the variables
  LTexture();

  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(std::string path);

  // Deallocates texture
  void free();

  // Renders texture at given point
  void render(int x, int y, SDL_Rect *clip = NULL);

  // Sets the texture color modulation
  void setColor(Uint8 r, Uint8 g, Uint8 b);

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

void LTexture::render(int x, int y, SDL_Rect *clip) {
  // Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

LTexture gModulatedTexture;

bool loadMedia() {
  // Load foo texture
  if (!gModulatedTexture.loadFromFile("12_color_modulation/colors.png")) {
    printf("Failed to load Foo texture image!\n");
    return false;
  }

  return true;
}

void close() {
  // Free loaded images
  gModulatedTexture.free();

  // Destroy Window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL substems.
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
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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

  // While application is running
  bool quit = false;
  SDL_Event e;
  Uint8 r = 255;
  Uint8 g = 255;
  Uint8 b = 255;

  if (!loadMedia()) {
    return 1;
  }

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_q:
          r += 32;
          break;

        case SDLK_w:
          g += 32;
          break;

        case SDLK_e:
          b += 32;
          break;

        case SDLK_a:
          r -= 32;
          break;

        case SDLK_s:
          g -= 32;
          break;

        case SDLK_d:
          b -= 32;
          break;
        }
      }
    }

    // Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // Modulate and render texture
    gModulatedTexture.setColor(r, g, b);
    gModulatedTexture.render(0, 0);

    SDL_RenderPresent(gRenderer);
  }
  close();
}
