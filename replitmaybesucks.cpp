#include <SDL2/SDL.h>
#include <iostream>
#define SCREENW 800
#define SCREENH 800
using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;

void makeShape(int w, int h, int r, int g, int b) {
  SDL_Rect rect;
  rect.w = w;
  rect.h = h;
  rect.x = (SCREENW - w) / 2;
  rect.y = (SCREENH - h) / 2;
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void initSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
  }

  window = SDL_CreateWindow("Pulp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREENW, SCREENH, SDL_WINDOW_RESIZABLE);

  if (window == NULL) {
    cout << "Window could not be created! SDL_Error: " << SDL_GetError()
         << endl;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
    cout << "Renderer could not be created! SDL_Error: " << SDL_GetError()
         << endl;
  }
}

void quitSdl(SDL_Window *window, SDL_Renderer *renderer) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main() {
  initSDL();
  SDL_Event e;
  bool isRunning = true;

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            isRunning = false;
            break;
        }
      }
    }

    makeShape(100, 100, 255, 0, 0); // Draw a red rectangle

    SDL_RenderPresent(renderer);
  }

  quitSdl(window, renderer);
  return 0;
}
