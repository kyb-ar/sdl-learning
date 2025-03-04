// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

// The window we'll be rendering to.
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and how on the screen
SDL_Surface *gHelloWorld = NULL;

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

bool loadMedia() {
  gHelloWorld =
      SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");

  if (gHelloWorld == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n",
           "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
    return false;
  }

  return true;
}

void close() {
  // Deallocate surface
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize!\n");
    close();
    return 1;
  }

  if (!loadMedia()) {
    printf("Failed to load media!\n");
    close();
    return 1;
  }

  SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

  // Update the surface
  SDL_UpdateWindowSurface(gWindow);

  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }
  }

  close();

  return 0;
}
