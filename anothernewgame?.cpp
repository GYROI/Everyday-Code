#include <iostream>
#include <SDL2/SDL.h>
#include <windows.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

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

    window = SDL_CreateWindow("Rotation Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

SDL_Rect rectdot = {0, 0, 50, 50};
SDL_Rect wallrect = {650, 100, 200, 500};

uint32_t movement = 5;

bool checkWindowCollision(const SDL_Rect& rect, int windowWidth, int windowHeight) {
    return (
        rect.x >= 0 &&
        rect.y >= 0 &&
        rect.x + rect.w <= windowWidth &&
        rect.y + rect.h <= windowHeight
    );
}

int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;
    SDL_Texture* bg = loadTexture("D://background.bmp", renderer);
    SDL_Texture* dot = loadTexture("D://dot.bmp", renderer);
    SDL_Texture* wall = loadTexture("D://wall.bmp", renderer);
    if (bg == nullptr || dot == nullptr || wall == nullptr) {
        cout << "IMAGE CAN'T BE LOADED" << SDL_GetError() << endl;
        isRunning = false;
    }

    while (isRunning) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
               switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_a:
                    if (checkWindowCollision(rectdot, SCREEN_WIDTH, SCREEN_HEIGHT)) {
                        rectdot.x -= movement;
                    }
                    break; // Add break statement here
                case SDLK_d:
                    if (checkWindowCollision(rectdot, SCREEN_WIDTH, SCREEN_HEIGHT)) {
                        rectdot.x += movement;
                    }
                    break; // Add break statement here
                case SDLK_w:
                    if (checkWindowCollision(rectdot, SCREEN_WIDTH, SCREEN_HEIGHT)) {
                        rectdot.y -= movement;
                    }
                    break; // Add break statement here
                case SDLK_s:
                    if (checkWindowCollision(rectdot, SCREEN_WIDTH, SCREEN_HEIGHT)) {
                        rectdot.y += movement;
                    }
                    break; // Add break statement here
                }

            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, nullptr, nullptr);
        SDL_RenderCopy(renderer, dot, nullptr, &rectdot);
        SDL_RenderCopy(renderer, wall, nullptr, &wallrect);
        SDL_RenderPresent(renderer);
    }

    quitSDL();
    return 0;
}
