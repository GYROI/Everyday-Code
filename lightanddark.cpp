#include <SDL2/SDL.h>
#include <iostream>
#undef main

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Painter App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l) {
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d){
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
            }
        }
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
