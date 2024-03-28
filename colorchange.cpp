#include <SDL2/SDL.h>
#include <iostream>
#include <cmath> // For abs()
#undef main
using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
int temperature = 0;
SDL_Color backgroundColor = {0, 0, 0, 255};
SDL_Rect rect = {375, 275, 50, 50};

void init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL Initialization Failed: " << SDL_GetError() << endl;
        return;
    }

    window = SDL_CreateWindow("Temperature Color Changer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Window Creation Failed: " << SDL_GetError() << endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "Renderer Creation Failed: " << SDL_GetError() << endl;
        return;
    }
}

void update() {
    // Update background color based on temperature
    int redComponent = min(255, 255 * abs(temperature) / 100);
    int blueComponent = min(255, 255 * (100 - abs(temperature)) / 100);
    backgroundColor = {redComponent, 0, blueComponent, 255};

    // Update box size based on temperature
    rect.w = 50 + temperature / 2;
    rect.h = 50 + temperature / 2;
}

void render() {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 233, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

int main() {
    init();
    if (window == NULL || renderer == NULL) {
        // Exit if initialization failed
        SDL_Quit();
        return -1;
    }

    bool isPlaying = true;
    SDL_Event e;

    while (isPlaying) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isPlaying = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_UP) {
                    temperature += 10;
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    temperature -= 10;
                }
                // Ensure temperature stays within -100 to 100 range
                temperature = min(100, max(-100, temperature));
                update();
            }
        }
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
