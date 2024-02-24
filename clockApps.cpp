#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main
using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

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

    window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        cout << "SDL_ttf couldn't be initiated: " << TTF_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Load a font
    font = TTF_OpenFont("D://Gotham Bold.ttf", 42);
    if (font == nullptr) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void quitSDL() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y) {
    SDL_Color textColor = {255, 255, 255};  // White color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect renderRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
string getCurrentTime(){
    time_t clock = time(nullptr);
    struct tm* now = localtime(&clock);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", now);
    return buffer;

}

string getCurrentDate(){
    time_t date = time(nullptr);
    struct tm* now = localtime(&date);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", now);
    return buffer;

}
int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;

    while (isRunning) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the current time
        string currentTime = getCurrentTime();
        string currentDate = "Today is "+ getCurrentDate();
        renderText(renderer, currentDate, 250, 223);
        renderText(renderer, currentTime, 250, 277 );

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Delay for 1 second
        SDL_Delay(1000);
    }

    quitSDL();
    return 0;
}

