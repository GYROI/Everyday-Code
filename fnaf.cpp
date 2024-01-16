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
    initSDL(window, renderer, "Press W");
    SDL_Event e;
    bool irun = true;

    SDL_Texture* textureBG = loadTexture("D:/black.bmp");
    SDL_Texture* goodscene = loadTexture("D:/grimoooooooooo.bmp");

    if (textureBG == nullptr || goodscene == nullptr) {
        cout << "Failed to load texture!" << endl;
        return -1;
    }

    SDL_Texture* currentTexture = textureBG;
    bool displayGoodScene = false;

    while (irun) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                irun = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_w) {
                    displayGoodScene = !displayGoodScene;
                    currentTexture = displayGoodScene ? goodscene : textureBG;
                }
            }
        }

        SDL_RenderClear(renderer);

        rect(renderer, currentTexture, 0, 0, SCREENW, SCREENH);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureBG);
    SDL_DestroyTexture(goodscene);
    quitSDL();

    return 0;
}
