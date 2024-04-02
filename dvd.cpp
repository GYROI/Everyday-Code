#include <SDL2/SDL.h>
#include <iostream>
#undef main
// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// DVD logo dimensions
const int DVD_WIDTH = 200;
const int DVD_HEIGHT = 100;

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Bouncing DVD Logo",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // DVD logo texture
    SDL_Surface* dvdSurface = SDL_LoadBMP("dvd.bmp");
    if (dvdSurface == nullptr) {
        std::cerr << "Failed to load DVD logo! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Texture* dvdTexture = SDL_CreateTextureFromSurface(renderer, dvdSurface);
    SDL_FreeSurface(dvdSurface);
    if (dvdTexture == nullptr) {
        std::cerr << "Failed to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set initial position and velocity of DVD logo
    int x = 0;
    int y = 0;
    int dx = 5;
    int dy = 5;

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render DVD logo
        SDL_Rect dstRect = {x, y, DVD_WIDTH, DVD_HEIGHT};
        SDL_RenderCopy(renderer, dvdTexture, nullptr, &dstRect);

        // Update position of DVD logo
        x += dx;
        y += dy;

        // Bounce off edges
        if (x < 0 || x + DVD_WIDTH > WINDOW_WIDTH) {
            dx *= -1;
        }
        if (y < 0 || y + DVD_HEIGHT > WINDOW_HEIGHT) {
            dy *= -1;
        }

        // Update
        SDL_RenderPresent(renderer);
        // Delay to control frame rate
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyTexture(dvdTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
