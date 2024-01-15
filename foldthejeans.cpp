#include <iostream>
#include <SDL2/SDL.h>
#include "windows.h"
#define SCREENW 800
#define SCREENH 600
#undef main
using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Texture* loadTexture(const std::string& filePath) {
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

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* gameTitle) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL couldn't be initiated: " << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_MAXIMIZED);
    if (window == nullptr) {
        cout << "Window couldn't be created: " << SDL_GetError() << endl;
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer couldn't be created: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void rect(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect rectd = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rectd);
}

int main() {
    initSDL(window, renderer, "Fold the Jeans");
    SDL_Event e;
    bool irun = true;

    SDL_Texture* textureBG = loadTexture("D:/yellowbg.bmp");
    SDL_Texture* tidied = loadTexture("D:/tidied.bmp");
    SDL_Texture* f1 = loadTexture("D:/f1.bmp");
    SDL_Texture* folded = loadTexture("D:/done.bmp");

    if (textureBG == nullptr || tidied == nullptr || f1 == nullptr || folded == nullptr) {
        cout << "Failed to load texture!" << endl;
        return -1;
    }

    int tidiedX = (SCREENW - 100) / 2;
    int tidiedY = (SCREENH - 200) / 2;
    SDL_Texture* currentTexture = tidied;  // Initially set to tidied

    while (irun) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                irun = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_a) {
                    SDL_DestroyTexture(currentTexture);
                    currentTexture = f1;
                } else if (e.key.keysym.sym == SDLK_w) {
                    SDL_DestroyTexture(currentTexture);
                    currentTexture = folded;
                    irun = false;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textureBG, NULL, NULL);


        rect(renderer, currentTexture, tidiedX, tidiedY, 100, 200);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureBG);
    quitSDL();

    return 0;
}
