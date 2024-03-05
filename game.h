#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>
using namespace std;
class Game{
    public :
        void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
        void close(SDL_Window*& window, SDL_Renderer*& renderer);
        void capFrame(Uint32 startticks);
        SDL_Texture* loadTexture(SDL_Renderer*& renderer, const string& path);
        bool checkCol(SDL_Rect& P, SDL_Rect& B);
        void returnMario(SDL_Rect& marioRect);
        void Score(SDL_Renderer*& renderer, TTF_Font*& font, const char* text, SDL_Color& color, int x, int y);
};

#endif // GAME_H


