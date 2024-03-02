#include "game.h"
#include <iostream>
#define SCREENW 800
#define SCREENH 600
using namespace std;
#undef main

void Game::initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout << "SDL CANT BE INITIATED" << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow("Game using classes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        cout << "Window cant be made" << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        cout << "Renderer cant be made" << SDL_GetError() << endl;
    }
}

void Game::close(SDL_Window*& window, SDL_Renderer*& renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
int main(){
    SDL_Window* window;
    SDL_Renderer* renderer;

    Game meGame;

    meGame.initSDL(window, renderer);

    SDL_Event e;
    bool isRunning = true;

    while(isRunning){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                isRunning = false;
            } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }

        }
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    meGame.close(window, renderer);
    return 0;
}

