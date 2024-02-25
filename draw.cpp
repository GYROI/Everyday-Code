#include <SDL2/SDL.h>
#include <iostream>
#undef main

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Painter App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);  // Set draw color to white

    return true;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void draw(SDL_Point& startPoint, SDL_Point& endPoint) {
    SDL_RenderDrawLine(gRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    SDL_Point startPoint{-1, -1};
    SDL_Point endPoint{-1, -1};

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&startPoint.x, &startPoint.y);
            } else if (e.type == SDL_MOUSEMOTION && startPoint.x != -1) {
                SDL_GetMouseState(&endPoint.x, &endPoint.y);
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);  // Set draw color to black
                draw(startPoint, endPoint);
            } else if (e.type == SDL_MOUSEBUTTONUP && startPoint.x != -1) {
                SDL_GetMouseState(&endPoint.x, &endPoint.y);
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);  // Set draw color to black
                draw(startPoint, endPoint);
                startPoint.x = startPoint.y = endPoint.x = endPoint.y = -1;
            }
        }

        // Move these outside the event loop
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
