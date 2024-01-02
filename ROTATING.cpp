#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#undef main

// Function to draw a rotated rectangle
void drawRotatedRectangle(SDL_Renderer* renderer, int x, int y, int width, int height, double angle) {
    SDL_Point points[5]; // 4 points for the rectangle plus one to close the shape
    double radians = angle * M_PI / 180.0; // Convert angle to radians

    // Calculate the four corners of the rotated rectangle
    points[0] = { x, y };
    points[1] = { x + width * cos(radians), y + width * sin(radians) };
    points[2] = { x + width * cos(radians) - height * sin(radians), y + width * sin(radians) + height * cos(radians) };
    points[3] = { x - height * sin(radians), y + height * cos(radians) };

    // Close the shape by repeating the first point
    points[4] = points[0];

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set colour (red in this case)
    SDL_RenderDrawLines(renderer, points, 5); // Draw lines connecting the points to create the rotated rectangle
}

int main() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const double ROTATION_SPEED = 10.0; // Speed of rotation (adjust as needed)

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Rotating Rectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    double angle = 0.0; // Initial angle of rotation
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT) {
                angle += ROTATION_SPEED; // Increment angle on right arrow key press
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set background color (white)
        SDL_RenderClear(renderer);

        int centerX = SCREEN_WIDTH / 2;
        int centerY = SCREEN_HEIGHT / 2;
        int rectWidth = 200;
        int rectHeight = 100;

        drawRotatedRectangle(renderer, centerX - rectWidth / 2, centerY - rectHeight / 2, rectWidth, rectHeight, angle);

        SDL_RenderPresent(renderer); // Update screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
