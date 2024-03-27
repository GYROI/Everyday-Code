#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define BALL_SIZE 20
#define BALL_SPEED 5

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct {
    int x, y, w, h;
} Rect;

typedef struct {
    int x, y, w, h, dx, dy;
} Ball;

Rect paddle;

Ball ball;

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Catch the Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    return true;
}

void initGame() {
    paddle.x = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    paddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;

    ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
    ball.w = BALL_SIZE;
    ball.h = BALL_SIZE;

    srand(time(NULL));
    ball.dx = rand() % 2 == 0 ? BALL_SPEED : -BALL_SPEED;
    ball.dy = -BALL_SPEED;
}

void drawRect(Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect sdl_rect = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderFillRect(renderer, &sdl_rect);
}

void gameLoop() {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT] && paddle.x > 0) {
            paddle.x -= 5;
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT] && paddle.x < SCREEN_WIDTH - paddle.w) {
            paddle.x += 5;
        }

        ball.x += ball.dx;
        ball.y += ball.dy;

        // Ball-Paddle Collision
        if (ball.y + ball.h >= paddle.y && ball.x + ball.w >= paddle.x && ball.x <= paddle.x + paddle.w) {
            ball.dy = -ball.dy;
        }

        // Ball-Wall Collision
        if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - ball.w) {
            ball.dx = -ball.dx;
        }
        if (ball.y <= 0) {
            ball.dy = -ball.dy;
        }

        // Ball miss
        if (ball.y >= SCREEN_HEIGHT) {
            initGame();
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawRect(paddle, 0, 0, 0, 255);
        drawRect((Rect){ball.x, ball.y, ball.w, ball.h}, 255, 0, 0, 255);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!initializeSDL()) {
        printf("Failed to initialize SDL!\n");
        return 1;
    }

    initGame();

    gameLoop();

    closeSDL();

    return 0;
}
