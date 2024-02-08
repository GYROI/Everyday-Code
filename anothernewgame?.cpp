#include <iostream>
#include <SDL2/SDL.h>
#include <windows.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Rect rectdot = {0, 0, 50, 50};
SDL_Rect wallrect = {650, 100, 200, 500};

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

void capFrameRate(Uint32 startTicks) {
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    Uint32 currentTicks = SDL_GetTicks();
    Uint32 frameTicks = currentTicks - startTicks;

    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}

void loadNextWindow(SDL_Renderer* renderer, SDL_Texture*& oldBg, SDL_Texture* newBG, SDL_Texture*& dot, SDL_Texture*& wall, SDL_Rect dotrect) {
    // Load new textures
    SDL_Texture* newWall = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//wall.bmp", renderer);

    // Render new scene
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, newBG, nullptr, nullptr);
    SDL_RenderCopy(renderer, dot, nullptr, &dotrect);
    SDL_RenderCopy(renderer, newWall, nullptr, &wallrect);
    SDL_RenderPresent(renderer);

    // Destroy old wall texture
    SDL_DestroyTexture(wall);

    // Update textures
    oldBg = newBG;
    wall = newWall;
}

uint32_t movement = 10;

int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;
    SDL_Texture* bg = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//background.bmp", renderer);
    SDL_Texture* dot = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//dot.bmp", renderer);
    SDL_Texture* wall = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//wall.bmp", renderer);
    SDL_Texture* newBg = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//sky.bmp", renderer);
    if (bg == nullptr || dot == nullptr || wall == nullptr || newBg == nullptr) {
        cout << "IMAGE CAN'T BE LOADED" << SDL_GetError() << endl;
        isRunning = false;
    }

    while (isRunning) {
        Uint32 startTicks = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                } else if(e.key.keysym.sym == SDLK_a){
                    rectdot.x -= movement;
                } else if(e.key.keysym.sym == SDLK_d){
                    rectdot.x += movement;
                } else if(e.key.keysym.sym == SDLK_w){
                    rectdot.y -= movement;
                } else if(e.key.keysym.sym == SDLK_s){
                    rectdot.y += movement;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, nullptr, nullptr);
        SDL_RenderCopy(renderer, dot, nullptr, &rectdot);
        SDL_RenderCopy(renderer, wall, nullptr, &wallrect);

        if (rectdot.x < wallrect.x + wallrect.w && rectdot.x + rectdot.w > wallrect.x && rectdot.y < wallrect.y + wallrect.h &&
            rectdot.y + rectdot.h > wallrect.y)
        {
            loadNextWindow(renderer, bg, newBg, dot, wall, rectdot);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }

        SDL_RenderPresent(renderer);

        capFrameRate(startTicks);
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(dot);
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(newBg);
    quitSDL();
    return 0;
}
