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

    wavSpec.callback = nullptr;  // No callback function
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

    // Add a small delay to allow SDL to handle audio
    SDL_Delay(100); // Adjust the delay as needed

    // Wait until audio playback is finished
    while (SDL_GetQueuedAudioSize(1) > 0) {
        SDL_Delay(10);
    }

    // Close the audio device
    SDL_CloseAudio();
}



SDL_Texture* startTexture = nullptr;

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
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    // Handle left click
                    playAudio("D://ahhhhhhhhh.wav");
                    SDL_Delay(2000);
                }
            }
        }

        SDL_RenderClear(renderer);
        rect(renderer, startTexture, (SCREENW - 400) / 2, (SCREENH - 300) / 2, 400, 300);
        SDL_RenderPresent(renderer);
    }

    quitSDL();

    return 0;
}
