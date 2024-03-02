#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;

    class Game{
    public :
        void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
        void close(SDL_Window*& window, SDL_Renderer*& renderer);
        void loadTexture(SDL_Texture* texture, const string& path);
    };

#endif // GAME_H


