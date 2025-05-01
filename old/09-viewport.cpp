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

SDL_Rect topLeftViewPort;

void close() {
  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
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
  SDL_Rect topLeftViewport;
  topLeftViewport.x = 0;
  topLeftViewport.y = 0;
  topLeftViewport.w = SCREEN_WIDTH / 2;
  topLeftViewport.h = SCREEN_HEIGHT / 2;

  SDL_Rect topRightViewport;
  topRightViewport.x = SCREEN_WIDTH / 2;
  topRightViewport.y = 0;
  topRightViewport.w = SCREEN_WIDTH / 2;
  topRightViewport.h = SCREEN_HEIGHT / 2;

  SDL_Rect bottomViewport;
  bottomViewport.x = 0;
  bottomViewport.y = SCREEN_HEIGHT / 2;
  bottomViewport.w = SCREEN_WIDTH;
  bottomViewport.h = SCREEN_HEIGHT / 2;

  SDL_Rect fillRect = {0, 0, 20, 20};
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // Top left viewport draw
    SDL_RenderSetViewport(gRenderer, &topLeftViewport);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    // Top right viewport draw
    SDL_RenderSetViewport(gRenderer, &topRightViewport);
    SDL_SetRenderDrawColor(gRenderer, 0x44, 0x00, 0x44, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    // Bottom viewport draw
    SDL_RenderSetViewport(gRenderer, &bottomViewport);
    SDL_SetRenderDrawColor(gRenderer, 0x44, 0xFF, 0x44, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

    SDL_RenderPresent(gRenderer);
  }
  close();
}
