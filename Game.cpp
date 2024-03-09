#include "Game.h"
#include <iostream>
#include <string>
#define SCREENW 800
#define SCREENH 600
using namespace std;
#undef main

void Game::initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout << "SDL CANT BE INITIATED" << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow("Plane Prevention", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        cout << "Window cant be made" << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        cout << "Renderer cant be made" << SDL_GetError() << endl;
    }


}

void Game::capFrame(Uint32 startticks){
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    Uint32 currentTicks = SDL_GetTicks();
    Uint32 frameTicks = currentTicks - startticks;

    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}
SDL_Texture* Game::loadTexture(SDL_Renderer*& renderer, const string& path){
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if(surface == nullptr){
        cout <<"Surface cant be loaded"<< SDL_GetError() << endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == nullptr){
        cout <<"Texture cant be loaded"<< SDL_GetError() << endl;
    }

    return texture;
}

bool Game::checkCol(SDL_Rect& P, SDL_Rect& B) {
    // Check for horizontal collision
    bool horizontalCollision = (P.x + P.w) <= B.x || P.x >= (B.x + B.w);

    // Check for vertical collision
    bool verticalCollision = (P.y + P.h) <= B.y || P.y >= (B.y + B.h);

    // Return true if there is no collision (both horizontal and vertical)
    return !(horizontalCollision || verticalCollision);
}

void Game::close(SDL_Window*& window, SDL_Renderer*& renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main(){
    Game newG;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect planeS = {0,229, 200, 140};
    newG.initSDL(window, renderer);

    SDL_Texture* plane = newG.loadTexture(renderer, "C:/Users/User/Desktop/SDL/3d/gameText/aero.bmp");

    SDL_Event e;
    bool isPlaying = true;

    while(isPlaying){
        Uint32 starticks = SDL_GetTicks();
          while(SDL_PollEvent(&e)!=0){
            if(e.type == SDL_QUIT){
                SDL_Quit();
            } else if(e.key.keysym.sym == SDLK_w){
                planeS.x += 10;
            }
          }
          SDL_RenderClear(renderer);
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_RenderCopy(renderer, plane, nullptr, &planeS);
          SDL_RenderPresent(renderer);
          newG.capFrame(starticks);
    }

    newG.close(window, renderer);
    return 0;
}
