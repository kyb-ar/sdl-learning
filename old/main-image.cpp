// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <list>
#include <stdio.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

bool init();
void close();

// Loads individual image
SDL_Surface *loadSurface(std::string path);

// The window we'll be rendering to.
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *gCurrentSurface = NULL;

SDL_Surface *loadSurface(std::string path) {
  // Load image at specified path
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());

  return loadedSurface;
}

SDL_Surface *loadMedia(std::string path) {
  SDL_Surface *optimizedSurface = NULL;
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    printf("unable to load image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
    return NULL;
  }

  // Convert surface to screen format
  optimizedSurface =
      SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
  SDL_FreeSurface(loadedSurface);
  if (optimizedSurface == NULL) {
    printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
    return NULL;
  }
  return optimizedSurface;
}

bool init() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialze! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (gWindow == NULL) {
    return false;
  }

  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize!\n");
    close();
    return 1;
  }

  std::list<std::string> files = {
      "04_key_presses/press.bmp", "04_key_presses/up.bmp",
      "04_key_presses/down.bmp",  "04_key_presses/left.bmp",
      "04_key_presses/right.bmp",
  };

  int i = 0;
  for (const std::string &file : files) {
    gKeyPressSurfaces[i] = loadMedia(file);
    i++;
  }

  SDL_Event e;
  bool quit = false;
  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      if (e.type == SDL_KEYDOWN) {

        switch (e.key.keysym.sym) {
        case SDLK_UP:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
          break;

        case SDLK_DOWN:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
          break;

        case SDLK_LEFT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
          break;

        case SDLK_RIGHT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
          break;

        default:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
          break;
        }
      }
      SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);
    }
  }

  close();

  return 0;
}
