#include <iostream>
#include <SDL2/SDL.h>

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
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
    initSDL(window, renderer, "It will become larger");
    SDL_Event e;
    bool irun = true;

    int smileX = (SCREENW - 200) / 2;
    int smileY = (SCREENH - 200) / 2;
    int smilew = 200;
    int smileh = 200;

    SDL_Texture* smile = loadTexture("D:\\justsmile.bmp");

    while (irun) {
        SDL_RenderClear(renderer);

        smilew += 1;
        smileh += 1;

        // Adjust position to center the resizing
        smileX = (SCREENW - smilew) / 2;
        smileY = (SCREENH - smileh) / 2;

        rect(renderer, smile, smileX, smileY, smilew, smileh);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                irun = false;
            } else if(smileX == SCREENW && smileY == SCREENH){
                irun = false;
            }
        }
    }

    SDL_DestroyTexture(smile);
    quitSDL();

    return 0;
}
