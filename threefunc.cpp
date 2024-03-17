#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#undef main
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRAPH_WIDTH = 600;
const int GRAPH_HEIGHT = 400;
const int GRAPH_MARGIN = 50;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("Graphs of Trigonometric Functions",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void drawAxes() {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    // Draw x-axis
    SDL_RenderDrawLine(gRenderer, GRAPH_MARGIN, SCREEN_HEIGHT / 2,
        GRAPH_MARGIN + GRAPH_WIDTH, SCREEN_HEIGHT / 2);

    // Draw y-axis
    SDL_RenderDrawLine(gRenderer, GRAPH_MARGIN + GRAPH_WIDTH / 2, SCREEN_HEIGHT,
        GRAPH_MARGIN + GRAPH_WIDTH / 2, SCREEN_HEIGHT - GRAPH_HEIGHT);
}

void drawGraph(double (*function)(double), SDL_Color color) {
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);

    double step = 0.1;
    for (double x = -M_PI; x <= M_PI; x += step) {
        double y = function(x);
        int pixelX = GRAPH_MARGIN + (x + M_PI) * (GRAPH_WIDTH / (2 * M_PI));
        int pixelY = SCREEN_HEIGHT / 2 - y * (GRAPH_HEIGHT / 2);
        SDL_RenderDrawPoint(gRenderer, pixelX, pixelY);
    }
}

double sinFunction(double x) {
    return std::sin(x);
}

double cosFunction(double x) {
    return std::cos(x);
}

double tanFunction(double x) {
    return std::tan(x);
}

int main(int argc, char* args[]) {
    initSDL();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        drawAxes();
        drawGraph(sinFunction, {255, 0, 0});
        drawGraph(cosFunction, {0, 255, 0});
        drawGraph(tanFunction, {0, 0, 255});

        SDL_RenderPresent(gRenderer);
    }

    closeSDL();
    return 0;
}
