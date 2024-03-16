#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#undef main
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_RADIUS = 50;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool initSDL() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        gWindow = SDL_CreateWindow("Random Circles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }

    return success;
}

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void drawRandomCircles() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    srand(time(NULL));
    for (int i = 0; i < 50; ++i) {
        int centerX = rand() % SCREEN_WIDTH;
        int centerY = rand() % SCREEN_HEIGHT;
        int radius = rand() % MAX_RADIUS + 1;

        int red = rand() % 256;
        int green = rand() % 256;
        int blue = rand() % 256;

        SDL_SetRenderDrawColor(gRenderer, red, green, blue, 0xFF);
        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                if (x*x + y*y <= radius*radius) {
                    SDL_RenderDrawPoint(gRenderer, centerX + x, centerY + y);
                }
            }
        }
    }

    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[]) {
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        drawRandomCircles();
    }

    closeSDL();
    return 0;
}
