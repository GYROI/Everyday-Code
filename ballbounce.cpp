#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#undef main

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const double GRAVITY = 0.2; // Gravity constant
const double ELASTICITY = 0.8; // Bounciness

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Bouncing Ball Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    if (!initSDL()) {
        return 1;
    }

    SDL_Event e;
    bool isRunning = true;
    double time = 0.0;
    double posY = SCREEN_HEIGHT / 2; // Initial position
    double velocityY = -10; // Initial velocity

    while (isRunning) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Update position
        posY += velocityY;
        velocityY += GRAVITY;

        // Check collision with ground
        if (posY >= SCREEN_HEIGHT) {
            // Bounce (reverse velocity and apply elasticity)
            posY = SCREEN_HEIGHT; // Ensure ball is above ground
            velocityY = -velocityY * ELASTICITY;
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render ball
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect ballRect = {SCREEN_WIDTH / 2 - 10, static_cast<int>(posY) - 10, 20, 20}; // Ball size: 20x20
        SDL_RenderFillRect(renderer, &ballRect);

        // Render to screen
        SDL_RenderPresent(renderer);

        // Add delay to control frame rate
        SDL_Delay(16); // 60 FPS (1000 ms / 60 ≈ 16.67 ms per frame)
    }

    close();

    return 0;
}
