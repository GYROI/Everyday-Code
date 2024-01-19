#include <iostream>
#include <SDL2/SDL.h>

#define SCREENW 800
#define SCREENH 600

#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

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
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void rect(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect rectd = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rectd);
}

int main() {
    initSDL(window, renderer, "Smiley Window");

    SDL_Texture* smileTexture = loadTexture("D:\justsmile.bmp");  // Provide the correct path to your BMP file
    if (smileTexture == nullptr) {
        quitSDL();
        return 1;
    }

    SDL_Event e;
    bool irun = true;

    const char* wavFile = "D:\\ohshut_RVC_1.wav";
    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer;
    Uint32 wavLength;

    // Load the WAV file
    if (SDL_LoadWAV(wavFile, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        cout <<"Whats wrong is" << SDL_GetError() << endl;
        return 1;
    }

    // Open the audio device
    SDL_AudioDeviceID audioDevice;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (audioDevice == 0) {
        // Handle error
        SDL_FreeWAV(wavBuffer);
        quitSDL();
        return 1;
    }

    while (irun) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                irun = false;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
                SDL_PauseAudioDevice(audioDevice, 0);
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the smiley face at the center of the window
        int smileX = (SCREENW - 100) / 2;  // Adjust the position as needed
        int smileY = (SCREENH - 100) / 2;
        rect(renderer, smileTexture, smileX, smileY, 100, 100);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavBuffer);
    quitSDL();

    return 0;
}
