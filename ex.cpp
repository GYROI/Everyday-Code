#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#undef main
const int WIDTH = 800;
const int HEIGHT = 600;

// Function to plot: e^x
double function(double x) {
    return exp(x);
}

// Function to map x coordinate from real values to screen coordinates
int mapX(double x) {
    return (int)((x + 4) * WIDTH / 8);
}

// Function to map y coordinate from real values to screen coordinates
int mapY(double y) {
    return (int)((-y + 2) * HEIGHT / 4);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Math Graph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Plot the function
        SDL_RenderDrawPoint(renderer, mapX(0), mapY(function(0)));
        for (double x = -4; x <= 4; x += 0.01) {
            SDL_RenderDrawPoint(renderer, mapX(x), mapY(function(x)));
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
