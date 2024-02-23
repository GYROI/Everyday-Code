#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* currentTexture = nullptr;
SDL_Texture* newTexture = nullptr;

SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (surface == nullptr) {
        cout << "Failed to load image: " << SDL_GetError() << endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            cout << "Failed to create texture: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(surface);
    }
    return texture;
}

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL couldn't be initiated: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Music Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "Window couldn't be created: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer couldn't be created: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void capFrameRate(Uint32 startTicks) {
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    Uint32 currentTicks = SDL_GetTicks();
    Uint32 frameTicks = currentTicks - startTicks;

    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    float step = 0.1; // Adjust the step value for a smoother circle

    for (float angle = 0; angle < 2 * M_PI; angle += step) {
        int x1 = static_cast<int>(centerX + radius * cos(angle));
        int y1 = static_cast<int>(centerY + radius * sin(angle));

        int x2 = static_cast<int>(centerX + radius * cos(angle + step));
        int y2 = static_cast<int>(centerY + radius * sin(angle + step));

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;
    int radius = 1; // Initial radius value

    while (isRunning) {
        Uint32 startTicks = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            }
        }

        // Set the background color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw a red circle at the center of the window with the current radius
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        drawCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, radius);

        // Update the radius for the next frame
        radius += 2;

        SDL_RenderPresent(renderer);

        capFrameRate(startTicks);
    }

    // Release resources
    SDL_DestroyTexture(currentTexture);
    SDL_DestroyTexture(newTexture);
    quitSDL();

    return 0;
}
