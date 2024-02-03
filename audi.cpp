#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

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
    SDL_Delay(100); 

    // Wait until audio playback is finished
    while (SDL_GetQueuedAudioSize(1) > 0) {
        SDL_Delay(10);
    }

    // Close the audio device
    SDL_CloseAudio();
}
