#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#undef main
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Function to generate a random number in a given range
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Simple SDL Random Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set up the initial position and size of the rectangle
    SDL_Rect rectangle;
    rectangle.x = SCREEN_WIDTH / 2 - 25;
    rectangle.y = SCREEN_HEIGHT / 2 - 25;
    rectangle.w = 50;
    rectangle.h = 50;

    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Main loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Update the position of the rectangle
        rectangle.x = getRandomNumber(0, SCREEN_WIDTH - rectangle.w);
        rectangle.y = getRandomNumber(0, SCREEN_HEIGHT - rectangle.h);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the rectangle
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rectangle);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Introduce a slight delay to control the frame rate
        SDL_Delay(500);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
