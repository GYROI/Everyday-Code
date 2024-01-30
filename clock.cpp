#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <iostream>
#undef main

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* FONT_PATH = "D:\\Gotham Bold.ttf";
const int FONT_SIZE = 40;

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL initialization failed: " << SDL_GetError() << endl;
        return -1;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Live Clock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "SDL window creation failed: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        cout << "SDL renderer creation failed: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Color textColor = { 255, 255, 255, 255 };

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Get current time
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        char timeString[9]; // HH:MM:SS\0
        strftime(timeString, sizeof(timeString), "%T", localTime);

        // Render the time on the screen
        renderText(renderer, font, timeString, textColor, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50);

        // Update the renderer
        SDL_RenderPresent(renderer);

        // Add a small delay to control frame rate
        SDL_Delay(1000);
    }

    // Cleanup
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
