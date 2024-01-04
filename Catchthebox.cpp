#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_MOVE_SPEED = 100; // Movement speed for myRect

class Rect {
public:
    int x, y, w, h;

    Rect(int posX, int posY, int width, int height) : x(posX), y(posY), w(width), h(height) {}
};

// Function to render a rectangle
void renderRect(SDL_Renderer* renderer, const Rect& rect, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect sdlRect = { rect.x, rect.y, rect.w, rect.h };
    SDL_RenderFillRect(renderer, &sdlRect);
}

// Function to check collision between two rectangles
bool checkCollision(const Rect& a, const Rect& b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("CATCH THE BOXX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    Rect myRect(100, 500, 200, 500); // Creating an instance of Rect class
    Rect enemy(50, 50, 50, 50);
    int enemySpeed = 5; // Enemy downward speed

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                else if (e.key.keysym.sym == SDLK_a && myRect.x > 0) {
                    myRect.x -= RECT_MOVE_SPEED;
                }
                else if (e.key.keysym.sym == SDLK_d && myRect.x + myRect.w < SCREEN_WIDTH) {
                    myRect.x += RECT_MOVE_SPEED;
                }
            }
        }

        // Move enemy downwards
        enemy.y += enemySpeed;

        // Check collision between enemy and myRect
        if (checkCollision(enemy, myRect)) {
            enemy.y = SCREEN_HEIGHT + 100; // Move enemy off-screen if collision detected
        }

        // If enemy reaches bottom, reset its position
        if (enemy.y > SCREEN_HEIGHT) {
            enemy.y = 0;
            enemy.x = rand() % (SCREEN_WIDTH - enemy.w); // Randomize x position
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Render myRect
        renderRect(renderer, myRect, { 0x00, 0x00, 0xFF, 0xFF }); // Blue color

        // Render enemy
        renderRect(renderer, enemy, { 0xFF, 0x00, 0x00, 0xFF }); // Red color

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
