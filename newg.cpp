#include "game.h"
#include <iostream>
#define SCREENW 800
#define SCREENH 600
const int JUMPH = 100;
const int Gravity = 5;
using namespace std;
#undef main

void Game::initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout << "SDL CANT BE INITIATED" << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow("Just Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_SHOWN);
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

void Game::returnMario(SDL_Rect& marioRect){
    if(marioRect.x >= SCREENW){
        marioRect.x = 0 - marioRect.w;
    }
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
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect marioSize = {0, 473, 51, 53};
    SDL_Rect landS = {0, 526, 812, 90};
    SDL_Color windowCl = {255,255,255};
    SDL_Rect blockS = {374, 457, 52, 69};

    Game meGame;

    meGame.initSDL(window, renderer);

    SDL_Event e;
    bool isRunning = true;
    bool isJumping = false;
    int jumpH = 0;

    SDL_Texture* texture = meGame.loadTexture(renderer, "C:/Users/User/Desktop/SDL/mario/textures/t1.bmp");
    SDL_Texture* land = meGame.loadTexture(renderer, "C:/Users/User/Desktop/SDL/mario/textures/land.bmp");
    SDL_Texture* block = meGame.loadTexture(renderer, "C:/Users/User/Desktop/SDL/mario/textures/block.bmp");

    while(isRunning){
        Uint32 starticks = SDL_GetTicks();
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                isRunning = false;
            } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){
                if(!meGame.checkCol(marioSize, blockS)){
                     marioSize.x += 10;
                     meGame.returnMario(marioSize);
                }
            } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !isJumping){
                isJumping = true;
                jumpH = -40;
            }
        }

        if (isJumping && !meGame.checkCol(marioSize, blockS) ) {
            marioSize.y += jumpH;
            marioSize.x += 10;
            jumpH += Gravity;
            if (marioSize.y >= 473) {
                marioSize.y = 473;
                isJumping = false; // Reset jump state when on the ground
        }
    }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &marioSize);
        SDL_SetRenderDrawColor(renderer, windowCl.r, windowCl.g, windowCl.b, 255);
        SDL_RenderCopy(renderer, land, NULL, &landS);
        SDL_RenderCopy(renderer, block, NULL, &blockS);
        SDL_RenderPresent(renderer);

        meGame.capFrame(starticks);
    }

    meGame.close(window, renderer);
    return 0;
}

