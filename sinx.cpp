#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#undef main
class GraphRenderer {
public:
    GraphRenderer() : window(nullptr), renderer(nullptr) {}

    bool initSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow("Sin(x) Graph", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    void renderGraph() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            double y = SCREEN_HEIGHT / 2 - std::sin(static_cast<double>(x) / 50) * 50; // Adjust amplitude and frequency as needed
            SDL_RenderDrawPoint(renderer, x, static_cast<int>(y));
        }

        SDL_RenderPresent(renderer);
    }

    void close() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
};

int main() {
    GraphRenderer graphRenderer;

    if (!graphRenderer.initSDL()) {
        return 1;
    }

    SDL_Event e;
    bool isRunning = true;

    while (isRunning) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        graphRenderer.renderGraph();
    }

    graphRenderer.close();

    return 0;
}
