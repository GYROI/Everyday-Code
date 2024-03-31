#include <SDL2/SDL.h>
#include <iostream>
#undef main

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Rect bar = {173, 249, 455, 102};
SDL_Color bgColor = {255, 255, 255, 255}; // White background color

SDL_Rect load = {178, 259, 443, 80};
SDL_Color loadC = {104, 72, 16, 255};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Angry meter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    bool quit = false;
    bool pressed = false;

    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_a){
                    pressed = true;
                }
            }
        }

        if(pressed){
            load.w += 40;
            if(load.w >= bar.w) {
                load.w = bar.w;
            }
            pressed = false;
        } else {
            load.w -= 5;
            if(load.w <= 0){
                load.w = 0;
                quit = true;
            }
        }

        // Clear the renderer with the background color
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);

        // Draw the rectangle
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &bar);

        SDL_SetRenderDrawColor(renderer, loadC.r, loadC.g, loadC.b, loadC.a);
        SDL_RenderFillRect(renderer, &load);

        SDL_Delay(16);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
