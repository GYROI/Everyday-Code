#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#define SCREENW 800
#define SCREENH 600

#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

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

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* gameTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL couldn't be initiated: " << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_MAXIMIZED);
    if (window == nullptr) {
        cout << "Window couldn't be created: " << SDL_GetError() << endl;
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer couldn't be created: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Initialize SDL audio subsystem
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        cout << "SDL audio subsystem couldn't be initiated: " << SDL_GetError() << endl;
    }
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);  // Quit the audio subsystem
    SDL_Quit();
}

void rect(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect rectd = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rectd);
}

void audioCallback(void* userdata, Uint8* stream, int len) {
    // This callback is called when SDL needs more audio data.
    // You can fill the 'stream' buffer with audio data.
    // In this example, we're not loading a dynamic audio buffer, so we won't use this function.
}

void playAudio(const std::string& filePath) {
    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;

    if (SDL_LoadWAV(filePath.c_str(), &wavSpec, &wavStart, &wavLength) == nullptr) {
        cout << "Failed to load audio: " << SDL_GetError() << endl;
        return;
    }

    // Set the callback function
    wavSpec.callback = audioCallback;
    wavSpec.userdata = nullptr;

    // Open the audio device
    if (SDL_OpenAudio(&wavSpec, nullptr) < 0) {
        cout << "Failed to open audio device: " << SDL_GetError() << endl;
        SDL_FreeWAV(wavStart);
        return;
    }

    // Queue the audio data
    SDL_QueueAudio(1, wavStart, wavLength);
    SDL_FreeWAV(wavStart);

    // Start audio playback
    SDL_PauseAudio(0);
}

SDL_Texture* startTexture = nullptr;

int startW = 200;
int startH = 200;
int startX = (SCREENW - startW) / 2;
int startY = (SCREENH - startH) / 2;

bool clicked = false;

int main() {
    initSDL(window, renderer, "Smiley Window");

    startTexture = loadTexture("D:\\button.bmp", renderer);

    if (startTexture == nullptr) {
        quitSDL();
        return 1;
    }

    SDL_Event e;
    bool irun = true;

    while (irun) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                irun = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX >= startX && mouseX <= startX + startW &&
                    mouseY >= startY && mouseY <= startY + startH) {
                    // Left-clicked on the start image, change the texture and play audio
                    clicked = true;
                    playAudio("D:\\ahhhhhhhhh.wav");
                }
            }
        }

        SDL_RenderClear(renderer);
        rect(renderer, startTexture, 0, 0, SCREENW, SCREENH);
        SDL_RenderPresent(renderer);
    }

    quitSDL();

    return 0;
}
