#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib> // Include this header for rand() function
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

int main() {
    initSDL(window, renderer, "Pulp Game");
    SDL_Event e;
    bool irun = true;

    SDL_Texture* textureBG = loadTexture("D:/bg.bmp");
    SDL_Texture* textureburger = loadTexture("D:/pngtree-burger-vector-illustration-isolated-on-white-background-hamburger-clip-art-png-image_5067294-removebg-preview.bmp");
    SDL_Texture* textureGun = loadTexture("D:/png-transparent-gun-pistol-firearm-others-miscellaneous-handgun-airsoft.bmp");
    SDL_Texture* textureBullet = loadTexture("D:/images.bmp");
    if (textureBG == nullptr || textureburger == nullptr || textureGun == nullptr || textureBullet == nullptr) {
        cout << "Failed to load texture!" << endl;
        return -1;
    }

    int rectBurgerX = 5;

    SDL_Rect destbg = { 0, 0, SCREENW, SCREENH };
    SDL_Rect destRectBurger = { 0, 50, 100, 150 };
    SDL_Rect destRectPistol = { SCREENW - 250, 50, 200, 150 };
    SDL_Rect destRectBullet = { 500, destRectPistol.y + 50, 200, 150 }; // Bullet dimensions

    int rectPistolYMov = 25;
    bool burgerVisible = true;
    int respawnY = 50;
    bool bulletVisible = false;
    Uint32 lastShotTime = 0;
    Uint32 shootingDelay = 500;

    while (irun) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                irun = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_w) {
                    if (destRectPistol.y - rectPistolYMov >= 0) {
                        destRectPistol.y -= rectPistolYMov;
                    }
                } else if (e.key.keysym.sym == SDLK_s) {
                    if (destRectPistol.y + destRectPistol.h + rectPistolYMov <= SCREENH) {
                        destRectPistol.y += rectPistolYMov;
                    }
                }

                if (e.key.keysym.sym == SDLK_RETURN) {
                    Uint32 currentTime = SDL_GetTicks();
                    if (currentTime - lastShotTime >= shootingDelay) {
                        if (!bulletVisible) {
                            bulletVisible = true;
                            destRectBullet.x = destRectPistol.x;
                            destRectBullet.y = destRectPistol.y + destRectPistol.h / 2 - destRectBullet.h / 2;
                            lastShotTime = currentTime;  // Update the last shot time
                        }
                    }
                }
            }
        }

        destRectPistol.y = destRectPistol.y;
        destRectBurger.x -= 5; // Adjust the speed at which the burger moves on the x-axis
        if (destRectBurger.x + destRectBurger.w < 0) {
            respawnY = rand() % (SCREENH - destRectBurger.h);
            destRectBurger.x = SCREENW - destRectBurger.w; // Move the burger out of the screen on the x-axis
            destRectBurger.y = respawnY;
        }


        if (destRectBurger.x < destRectPistol.x + destRectPistol.w && destRectBurger.x + destRectBurger.w > destRectPistol.x &&
            destRectBurger.y < destRectPistol.y + destRectPistol.h && destRectBurger.y + destRectBurger.h > destRectPistol.y) {
            burgerVisible = false;
            respawnY = rand() % (SCREENH - destRectBurger.h); // Random respawn along the y-axis
            destRectBurger.x = SCREENW; // Move the burger out of the screen on the x-axis
            destRectBurger.y = respawnY; // Set the new y position for the respawned burger
        }

        if (bulletVisible) {
            destRectBullet.x -= 20; // Adjust bullet speed
            if (destRectBullet.x + destRectBullet.w < 0 || destRectBullet.x > SCREENW) {
                bulletVisible = false;
            }

            // Check for collision with burger
            if (destRectBullet.x < destRectBurger.x + destRectBurger.w &&
                destRectBullet.x + destRectBullet.w > destRectBurger.x &&
                destRectBullet.y < destRectBurger.y + destRectBurger.h &&
                destRectBullet.y + destRectBullet.h > destRectBurger.y) {
                burgerVisible = false;
                respawnY = rand() % (SCREENH - destRectBurger.h);
                destRectBurger.x = SCREENW; // Move the burger out of the screen on the x-axis
                destRectBurger.y = respawnY;
                bulletVisible = false; // Reset bullet visibility
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textureBG, NULL, &destbg);

        if (burgerVisible) {
            destRectBurger.y = respawnY;
            SDL_RenderCopy(renderer, textureburger, NULL, &destRectBurger);
        }

        SDL_RenderCopy(renderer, textureGun, NULL, &destRectPistol);

        if (bulletVisible) {
            SDL_RenderCopy(renderer, textureBullet, NULL, &destRectBullet);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureBullet);
    SDL_DestroyTexture(textureBG);
    SDL_DestroyTexture(textureburger);
    SDL_DestroyTexture(textureGun);
    quitSDL();

    return 0;
}
