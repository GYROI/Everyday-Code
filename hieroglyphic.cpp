#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Rect boxpoint = {0, 0, 40, 40}; // Starting point for 'a' and 'b'
uint32_t pointmovement = 40; // Initial movement value, set to boxpoint.w
vector<SDL_Rect> aBoxes; // Vector to store boxes for 'a'
vector<SDL_Rect> bBoxes; // Vector to store boxes for 'b'

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

    window = SDL_CreateWindow("Rotation Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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



void loadPoint(SDL_Texture* point, SDL_Rect& pointrect, vector<SDL_Rect>& boxes) {
    pointrect.x += pointmovement;

    // Check if the new box exceeds the right boundary
    if (pointrect.x + pointrect.w > SCREEN_WIDTH) {
        // Move to a new line
        pointrect.x = 0;
        pointrect.y += pointmovement;
    }

    // Check if the new box exceeds the bottom boundary
    if (pointrect.y + pointrect.h > SCREEN_HEIGHT) {
        // Reset to the top of the window
        pointrect.y = 0;
    }

    // Store the new box in the vector
    boxes.push_back(pointrect);
}

int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;
    SDL_Texture* bg = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//background.bmp", renderer);
    SDL_Texture* ah = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//a.bmp", renderer);
    SDL_Texture* bh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//b.bmp", renderer);
    if (bg == nullptr || ah == nullptr || bh == nullptr) {
        cout << "IMAGE CAN'T BE LOADED" << SDL_GetError() << endl;
        isRunning = false;
    }

    while (isRunning) {
        Uint32 startTicks = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                } else if (e.key.keysym.sym == SDLK_a) {
                    loadPoint(ah, boxpoint, aBoxes);
                    boxpoint.x+= (boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_b) {
                    loadPoint(bh, boxpoint, bBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, nullptr, nullptr);

        for (const auto& box : aBoxes) {
            SDL_RenderCopy(renderer, ah, nullptr, &box);
        }

        for (const auto& box : bBoxes) {
            SDL_RenderCopy(renderer, bh, nullptr, &box);
        }

        SDL_RenderPresent(renderer);
        capFrameRate(startTicks);
    }

    SDL_DestroyTexture(bg);

    quitSDL();

    return 0;
}
