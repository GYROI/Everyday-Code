#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#undef main
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Object dimensions
const int CHARACTER_SIZE = 20;
const int OBSTACLE_SIZE = 20;

// Structure to represent character
struct Character {
    int x, y;
    int velX, velY;
    Character() : x(SCREEN_WIDTH / 2), y(SCREEN_HEIGHT - CHARACTER_SIZE * 2), velX(0), velY(0) {}
};

// Structure to represent obstacle
struct Obstacle {
    int x, y;
    Obstacle() : x(rand() % (SCREEN_WIDTH - OBSTACLE_SIZE)), y(0) {}
};

int main(int argc, char* args[]) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create window
    SDL_Window* window = SDL_CreateWindow("Avoid the Squares", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Game variables
    Character character;
    std::vector<Obstacle> obstacles;
    bool quit = false;
    SDL_Event e;

    // Game loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Move character
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            character.velX = -1;
        } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            character.velX = 1;
        } else {
            character.velX = 0;
        }

        // Update character position
        character.x += character.velX * 5;

        // Generate obstacles
        if (rand() % 100 < 5) {
            obstacles.push_back(Obstacle());
        }

        // Move obstacles
        for (auto& obstacle : obstacles) {
            obstacle.y += 3;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Render character
        SDL_Rect characterRect = { character.x, character.y, CHARACTER_SIZE, CHARACTER_SIZE };
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &characterRect);

        // Render obstacles
        for (auto& obstacle : obstacles) {
            SDL_Rect obstacleRect = { obstacle.x, obstacle.y, OBSTACLE_SIZE, OBSTACLE_SIZE };
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &obstacleRect);
        }

        // Collision detection
        for (auto& obstacle : obstacles) {
            if (character.x < obstacle.x + OBSTACLE_SIZE &&
                character.x + CHARACTER_SIZE > obstacle.x &&
                character.y < obstacle.y + OBSTACLE_SIZE &&
                character.y + CHARACTER_SIZE > obstacle.y) {
                quit = true; // Game over
            }
        }

        // Update screen
        SDL_RenderPresent(renderer);

        // Slow down game
        SDL_Delay(10);
    }

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}
