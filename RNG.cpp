#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#define SCREENW 800
#define SCREENH 600
#undef main

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout <<"SDL CANT BE INITIATED" << SDL_GetError() << endl;
        SDL_Quit();
    }

    window = SDL_CreateWindow("RNG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        cout <<"Window cant be created"<< SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        cout <<"Renderer cant be created"<< SDL_GetError() << endl;
    }
}

void close(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int RNG(){
    srand((unsigned) time(NULL));
    int randomm = 1 + (rand()%2);

    return randomm;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& path){
    SDL_Surface* s = SDL_LoadBMP(path.c_str());
    if(s == nullptr){
        cout <<"CANT MAKE SURFACE"<< SDL_GetError() << endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FreeSurface(s);

    if (!texture) {
        cout << "TEXTURE CANT BE LOADED" << SDL_GetError() << endl;
        return nullptr;
    }

    return texture;
}

int main(){
    init();

    SDL_Event e;
    bool isPlaying = true;

    SDL_Texture* t1 = loadTexture(renderer, "C:/Users/User/Desktop/SDL/no/gametext/graveyard.bmp");
    SDL_Texture* t2 = loadTexture(renderer, "C:/Users/User/Desktop/SDL/no/gametext/cute.bmp");
    SDL_Texture* currentTexture;

    while (isPlaying){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                isPlaying = false;
            } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f){
                int getNum = RNG();
                if(getNum == 1){
                    currentTexture = t1;
                } else if(getNum == 2){
                    currentTexture = t2;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, currentTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}
