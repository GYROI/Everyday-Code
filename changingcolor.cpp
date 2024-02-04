#include <SDL2/SDL.h>
#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

void changeColor(SDL_Renderer* renderer, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void quitSdl(SDL_Window* window, SDL_Renderer* renderer) {
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
                    // Add cases for color changes
                    case SDLK_r:
                        changeColor(renderer, 255, 0, 0);  // Red
                        break;
                    case SDLK_g:
                        changeColor(renderer, 0, 255, 0);  // Green
                        break;
                    case SDLK_b:
                        changeColor(renderer, 0, 0, 255);  // Blue
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    quitSdl(window, renderer);
    return 0;
}
