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
        void capFrame(Uint32 startticks);
        SDL_Texture* loadTexture(SDL_Renderer*& renderer, const string& path);
        bool checkCol(SDL_Rect& P, SDL_Rect& B);
        void returnMario(SDL_Rect& marioRect);
};

#endif // GAME_H


