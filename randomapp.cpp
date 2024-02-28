#include <SDL2/SDL.h>
#include <iostream>
#undef main

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RECT_WIDTH = 50;
const int RECT_HEIGHT = 50;
const int RECT_SPEED = 5;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

int rectX = (WINDOW_WIDTH - RECT_WIDTH) / 2;
int rectY = (WINDOW_HEIGHT - RECT_HEIGHT) / 2;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Random Beginner App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }
}

void update() {
    // Move the rectangle horizontally
    rectX += RECT_SPEED;

    // If the rectangle goes off the screen, reset its position
    if (rectX > WINDOW_WIDTH) {
        rectX = -RECT_WIDTH;
    }
}

void render() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // Set background color to white
    SDL_RenderClear(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF); // Set rectangle color to blue
    SDL_Rect fillRect = { rectX, rectY, RECT_WIDTH, RECT_HEIGHT };
    SDL_RenderFillRect(gRenderer, &fillRect);

    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return -1;
    }

    bool quit = false;
    while (!quit) {
        handleEvents(quit);
        update();
        render();
    }

    close();

    return 0;
}
