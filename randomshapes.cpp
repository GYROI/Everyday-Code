#include <SDL2/SDL.h>
#include <cstdlib>
#undef main
// Function to generate a random number within a range
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Random Shapes",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool quit = false;
    while (!quit) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Generate and draw random shapes
        SDL_SetRenderDrawColor(renderer, random(0, 255), random(0, 255), random(0, 255), 255);
        int shapeType = random(0, 2); // 0: rectangle, 1: circle
        if (shapeType == 0) {
            SDL_Rect rect = { random(0, 800), random(0, 600), random(20, 100), random(20, 100) };
            SDL_RenderFillRect(renderer, &rect);
        } else {
            SDL_Rect rect = { random(0, 800), random(0, 600), random(20, 100), random(20, 100) };
            SDL_RenderFillRect(renderer, &rect);
        }

        // Render to the screen
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(1000 / 5); // 30 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
