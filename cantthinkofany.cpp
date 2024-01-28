#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

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

    window = SDL_CreateWindow("Text Input Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void rect(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect rectd = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rectd);
}

int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;

    SDL_Texture* house = loadTexture("D://house.bmp", renderer);
    if (house == nullptr) {
        cout << "IMAGE CAN'T BE LOADED" << SDL_GetError() << endl;
        isRunning = false;
    }

    int zoomFactor = 2; // Adjust the zoom factor as needed
    int doorX = 100;
    int doorY = 100;
    int initialDoorWidth = 100;
    int initialDoorHeight = 200;
    int doorWidth = initialDoorWidth;
    int doorHeight = initialDoorHeight;

    while (isRunning) {
        // Reset door position and size before processing events
        doorX = 100;
        doorY = 100;
        doorWidth = initialDoorWidth;
        doorHeight = initialDoorHeight;

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                } else if (e.key.keysym.sym == SDLK_w) {
                    // Zoom in on the door
                    doorWidth *= zoomFactor;
                    doorHeight *= zoomFactor;
                }
            }
        }

        SDL_RenderClear(renderer);



        SDL_RenderPresent(renderer);
    }

    quitSDL();
    return 0;
}
