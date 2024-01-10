#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib> // Include this header for rand() function

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

int main() {
    initSDL(window, renderer, "Pulp Game");
    SDL_Event e;
    bool irun = true;

    SDL_Texture* textureBG = loadTexture("D:/bg.bmp");
    SDL_Texture* textureburger = loadTexture("D:/pngtree-burger-vector-illustration-isolated-on-white-background-hamburger-clip-art-png-image_5067294-removebg-preview.bmp");
    SDL_Texture* textureGun = loadTexture("D:/png-transparent-gun-pistol-firearm-others-miscellaneous-handgun-airsoft.bmp");
    if (textureBG == nullptr || textureburger == nullptr || textureGun == nullptr) {
        cout << "Failed to load texture!" << endl;
        return -1;
    }

    int rectBurgerX = 5;

    SDL_Rect destbg = { 0, 0, SCREENW, SCREENH };
    SDL_Rect destRectBurger = { 0, 50, 100, 150 };
    SDL_Rect destRectPistol = { SCREENW - 250, 50, 200, 150 };
    int rectPistolYMov = 25;
    bool burgerVisible = true;
    int respawnY = 50;

    while (irun) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                irun = false;
            } else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_w){
                    if(destRectPistol.y - rectPistolYMov >= 0){
                        destRectPistol.y -= rectPistolYMov;
                    }
                } else if(e.key.keysym.sym == SDLK_s){
                     if (destRectPistol.y + destRectPistol.h + rectPistolYMov <= SCREENH) {
                        destRectPistol.y += rectPistolYMov;
                    }
                }
            }
        }

        destRectPistol.y = destRectPistol.y;
        destRectBurger.x += rectBurgerX;

        if (destRectBurger.x < destRectPistol.x + destRectPistol.w && destRectBurger.x + destRectBurger.w > destRectPistol.x &&
            destRectBurger.y < destRectPistol.y + destRectPistol.h && destRectBurger.y + destRectBurger.h > destRectPistol.y) {
            burgerVisible = false;
            destRectBurger.x = 0; // Reset X position of the burger
            respawnY = rand() % (SCREENH - destRectBurger.h);
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textureBG, NULL, &destbg);

        if (burgerVisible) {
            destRectBurger.y = respawnY;
            SDL_RenderCopy(renderer, textureburger, NULL, &destRectBurger);
        }

        SDL_RenderCopy(renderer, textureGun, NULL, &destRectPistol);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureBG);
    SDL_DestroyTexture(textureburger);
    SDL_DestroyTexture(textureGun);
    quitSDL();

    return 0;
}
