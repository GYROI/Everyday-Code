#include <iostream>
#include <SDL2/SDL.h>
#undef main
using namespace std;

const int SCREEN_W = 1680;
const int SCREEN_H = 1040;

class RECT {
public:
    int Posx, Posy, w, h;
    RECT(int x, int y, int width, int height) : Posx(x), Posy(y), w(width), h(height) {}
};

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL COULD NOT START!!" << SDL_GetError() << endl;
        return -1;
    }

    window = SDL_CreateWindow("SIZEUP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "CANNOT CREATE WINDOW: " << SDL_GetError() << endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "CANNOT INITIATE RENDERER: " << SDL_GetError() << endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;


    int width = 100;
    int height = 100;
    int recX = (SCREEN_W - width)/2;
    int recY = (SCREEN_H - height)/2;
    RECT meRect(recX, recY, width, height);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            } else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_w){
                    width += 10;
                } else if(e.key.keysym.sym == SDLK_h){
                    height += 10;
                } else if(e.key.keysym.sym == SDLK_a){
                    width -= 10;
                } else if(e.key.keysym.sym == SDLK_z){
                    height-=10;
                }
            }

            meRect.w = width;
            meRect.h = height;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_Rect rect = { meRect.Posx, meRect.Posy, meRect.w, meRect.h };
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
