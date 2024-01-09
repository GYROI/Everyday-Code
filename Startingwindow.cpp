#include <iostream>
#include <SDL2/SDL.h>
#define SCREENW 800
#define SCREENH 600
#undef main
using namespace std;

class RECT {
public:
    int Posx, Posy, w, h;
    RECT(int x, int y, int width, int height) : Posx(x), Posy(y), w(width), h(height) {}
};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;

// Function to load a texture from file
SDL_Texture* loadTexture(const std::string& filePath) {
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

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return -1;
    }

    window = SDL_CreateWindow("SDL Texture Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREENW, SCREENH, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return -1;
    }

    // Load a texture
    texture = loadTexture("D:/sky-mvehfqz6w2ges2dj.bmp");
    if (texture == nullptr) {
        cout << "Failed to load texture!" << endl;
        return -1;
    }

    bool startWindow = true; // Flag to determine if the start window is visible
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (startWindow && e.key.keysym.sym == SDLK_RETURN) {
                    startWindow = false; // Transition to the game window
                } else if (!startWindow && e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true; // Exit the game if in the game window
                }
            }
        }

        if (startWindow) {
            // Clear the renderer for start window
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            // Display start window text or image
            // You can render "Start Game" text or an image here
            // For simplicity, let's just clear the screen with a different color
        } else {
            // Clear the renderer for game window
            SDL_RenderClear(renderer);
            // Render the texture to the screen
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_Rect rect = { SCREENW / 2 - 50, SCREENH / 2 - 50, 100, 100 }; // Centered rectangle
            SDL_RenderFillRect(renderer, &rect);
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
