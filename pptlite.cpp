#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect backgroundRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Rect textureRect = {181, 300, 436, 218};

SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (surface == nullptr) {
        cout << "Failed to load image: " << SDL_GetError() << endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            cout << "Failed to create texture: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(surface);
    }
    return texture;
}

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL couldn't be initiated: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Music Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "Window couldn't be created: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer couldn't be created: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void capFrameRate(Uint32 startTicks) {
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    Uint32 currentTicks = SDL_GetTicks();
    Uint32 frameTicks = currentTicks - startTicks;

    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}

int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;
    SDL_Texture* currentTexture = loadTexture("C://Users//User//Desktop//SDL//no//gametext//background.bmp", renderer);
    SDL_Texture* newTexture = nullptr;

    if (currentTexture == nullptr) {
        cout << "IMAGE CAN'T BE PRINTED" << SDL_GetError() << endl;
        return 1;
    }

    while (isRunning) {
        Uint32 startTicks = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    // Load the new texture when right arrow is pressed
                    if (newTexture == nullptr) {
                        newTexture = loadTexture("C://Users//User//Desktop//SDL//no//gametext//graveyard.bmp", renderer);
                    }
                }
            }
        }

        SDL_RenderClear(renderer);

        // Render the background texture
        SDL_RenderCopy(renderer, currentTexture, nullptr, &backgroundRect);

        // Render the new texture on top of the background
        if (newTexture != nullptr) {
            SDL_RenderCopy(renderer, newTexture, nullptr, &textureRect);
        }

        SDL_RenderPresent(renderer);

        capFrameRate(startTicks);
    }

    // Release resources
    SDL_DestroyTexture(currentTexture);
    SDL_DestroyTexture(newTexture);
    quitSDL();

    return 0;
}
