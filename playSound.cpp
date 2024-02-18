    const char* wavFile = "D://Flowers On The Wall.wav";
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
