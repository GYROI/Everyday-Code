#include <SDL2/SDL.h>
#include <iostream>
#undef main
// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;tt

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Color Change", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            closeSDL();
            exit(0);
        }
    }
}

void drawScreen(SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int main() {
    if (!initSDL()) {
        return -1;
    }

    SDL_Color currentColor = {255, 255, 255, 255}; // Initial color (white)

    bool quit = false;
    while (!quit) {
        handleEvents();

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            currentColor.r = 255; // Change R (Red) component
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            currentColor.g = 255; // Change G (Green) component
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            currentColor.b = 255; // Change B (Blue) component
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            currentColor.r = 0; // Reset R (Red) component
            currentColor.g = 0; // Reset G (Green) component
            currentColor.b = 0; // Reset B (Blue) component
        }

        drawScreen(currentColor);
    }

    closeSDL();
    return 0;
}
