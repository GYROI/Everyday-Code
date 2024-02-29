#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <cmath>

#undef main
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL couldn't be initiated: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    gWindow = SDL_CreateWindow("Fade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        cout << "Window couldn't be created: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        cout << "Renderer couldn't be created: " << SDL_GetError() << endl;
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void quitSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        // Handle error (print an error message, return nullptr, etc.)
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        cout << "TEXTURE CANT BE LOADED" << SDL_GetError() << endl;
        return nullptr;
    }

    return texture;
}

void fadeOutTexture(SDL_Texture* texture) {
    for (int alpha = 255; alpha >= 0; alpha -= 5) {
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, texture, NULL, NULL);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(30);  // Adjust the delay to control the fading speed
    }
}

int main(int argc, char* args[]) {
    initSDL();
    SDL_Texture* texture = loadTexture(gRenderer, "C:/Users/User/Desktop/SDL/no/gametext/ graveyard.bmp");
    SDL_Event e;
    bool isPlaying = true;

    while (isPlaying) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f) {
                fadeOutTexture(texture);
            } else if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                isPlaying = false;
            }
        }
    }

    quitSDL();

    return 0;
}
