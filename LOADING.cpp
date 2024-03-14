#include <SDL2/SDL.h>
#include <iostream>
#undef main
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BAR_WIDTH = 400;
const int BAR_HEIGHT = 40;
const int TOTAL_PROGRESS = 100;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("Loading Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set render color
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    return true;
}

void close() {
    // Destroy window and renderer
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

void renderLoadingScreen(int progress) {
    // Clear screen
    SDL_RenderClear(gRenderer);

    // Render progress bar background
    SDL_Rect progressBarBg = {SCREEN_WIDTH / 2 - BAR_WIDTH / 2, SCREEN_HEIGHT / 2 - BAR_HEIGHT / 2, BAR_WIDTH, BAR_HEIGHT};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(gRenderer, &progressBarBg);

    // Render progress bar
    SDL_Rect progressBar = {SCREEN_WIDTH / 2 - BAR_WIDTH / 2, SCREEN_HEIGHT / 2 - BAR_HEIGHT / 2, progress * BAR_WIDTH / TOTAL_PROGRESS, BAR_HEIGHT};
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &progressBar);

    // Update screen
    SDL_RenderPresent(gRenderer);
}

int main() {
    // Initialize SDL
    if (!init()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    // Simulate loading by increasing progress
    for (int progress = 0; progress <= TOTAL_PROGRESS; ++progress) {
        // Render loading screen
        renderLoadingScreen(progress);

        // Simulate delay
        SDL_Delay(15);
    }

    // Close SDL
    close();

    return 0;
}
