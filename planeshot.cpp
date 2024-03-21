#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#define SCREENW 800
#define SCREENH 600

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

    // Initialize SDL audio subsystem
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        cout << "SDL audio subsystem couldn't be initiated: " << SDL_GetError() << endl;
    }
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);  // Quit the audio subsystem
    SDL_Quit();
}


SDL_Texture* startTexture = nullptr;

int main() {
    initSDL(window, renderer, "Red Rock");

    startTexture = loadTexture("C://Users//User//Desktop//SDL//g2//gameText//player.bmp", renderer);

    if (startTexture == nullptr) {
        quitSDL();
        return 1;
    }

    SDL_Rect player = {65, 273, 74, 65};
    int angle = 0;

    SDL_Event e;
    bool irun = true;

    while (irun) {
        while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
            irun = false;
        } else if (e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_d){
                angle = 0;
                if(player.x + player.w <= SCREENW){
                    player.x += 10;
                }
            } else if(e.key.keysym.sym == SDLK_a){
                angle = -180;
                if(player.x - player.w >= -65){
                    player.x -= 10;
                }
            } else if(e.key.keysym.sym == SDLK_w){
                angle = -90;
                if(player.y > 0){
                    player.y -= 10;
                }
            } else if(e.key.keysym.sym == SDLK_s){
                angle = 90;
                if(player.y <= 540){
                    player.y += 10;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderCopyEx(renderer, startTexture, nullptr, &player, angle, nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }

    }
    quitSDL();
    return 0;
}
