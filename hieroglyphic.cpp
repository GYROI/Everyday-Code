#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#undef main

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Rect boxpoint = {0, 0, 40, 40};
uint32_t pointmovement = 40;
vector<SDL_Rect> aBoxes;
vector<SDL_Rect> bBoxes;
vector<SDL_Rect> cBoxes;
vector<SDL_Rect> dBoxes;
vector<SDL_Rect> eBoxes;
vector<SDL_Rect> fBoxes;
vector<SDL_Rect> gBoxes;
vector<SDL_Rect> hBoxes;
vector<SDL_Rect> iBoxes;
vector<SDL_Rect> jBoxes;
vector<SDL_Rect> kBoxes;
vector<SDL_Rect> lBoxes;
vector<SDL_Rect> mBoxes;
vector<SDL_Rect> nBoxes;
vector<SDL_Rect> oBoxes;
vector<SDL_Rect> pBoxes;
vector<SDL_Rect> qBoxes;
vector<SDL_Rect> rBoxes;
vector<SDL_Rect> sBoxes;
vector<SDL_Rect> tBoxes;
vector<SDL_Rect> uBoxes;
vector<SDL_Rect> vBoxes;
vector<SDL_Rect> wBoxes;
vector<SDL_Rect> xBoxes;
vector<SDL_Rect> yBoxes;
vector<SDL_Rect> zBoxes;


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

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL couldn't be initiated: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Hieroglyphic Keyboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "Window couldn't be created: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer couldn't be created: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void capFrameRate(Uint32 startTicks) {
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    Uint32 currentTicks = SDL_GetTicks();
    Uint32 frameTicks = currentTicks - startTicks;

    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}



void loadPoint(SDL_Texture* point, SDL_Rect& pointrect, vector<SDL_Rect>& boxes) {
    pointrect.x += pointmovement;

    // Check if the new box exceeds the right boundary
    if (pointrect.x + pointrect.w > SCREEN_WIDTH) {
        // Move to a new line
        pointrect.x = 0;
        pointrect.y += pointmovement;
    }

    // Check if the new box exceeds the bottom boundary
    if (pointrect.y + pointrect.h > SCREEN_HEIGHT) {
        // Reset to the top of the window
        pointrect.y = 0;
    }

    // Store the new box in the vector
    boxes.push_back(pointrect);
}

int main() {
    initSDL();

    SDL_Event e;
    bool isRunning = true;
    SDL_Texture* bg = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//background.bmp", renderer);
    SDL_Texture* ah = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//a.bmp", renderer);
    SDL_Texture* bh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//b.bmp", renderer);
    SDL_Texture* ch = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//c.bmp", renderer);
    SDL_Texture* dh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//d.bmp", renderer);
    SDL_Texture* eh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//e.bmp", renderer);
    SDL_Texture* fh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//f.bmp", renderer);
    SDL_Texture* gh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//g.bmp", renderer);
    SDL_Texture* hh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//h.bmp", renderer);
    SDL_Texture* ih = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//i.bmp", renderer);
    SDL_Texture* jh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//j.bmp", renderer);
    SDL_Texture* kh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//k.bmp", renderer);
    SDL_Texture* lh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//l.bmp", renderer);
    SDL_Texture* mh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//m.bmp", renderer);
    SDL_Texture* nh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//n.bmp", renderer);
    SDL_Texture* oh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//o.bmp", renderer);
    SDL_Texture* ph = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//p.bmp", renderer);
    SDL_Texture* qh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//q.bmp", renderer);
    SDL_Texture* rh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//r.bmp", renderer);
    SDL_Texture* sh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//s.bmp", renderer);
    SDL_Texture* th = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//t.bmp", renderer);
    SDL_Texture* uh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//u.bmp", renderer);
    SDL_Texture* vh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//v.bmp", renderer);
    SDL_Texture* wh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//w.bmp", renderer);
    SDL_Texture* xh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//x.bmp", renderer);
    SDL_Texture* yh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//y.bmp", renderer);
    SDL_Texture* zh = loadTexture("C://Users//User//Desktop//SDL//wudooooo//gametext//z.bmp", renderer);

    if (bg == nullptr || ah == nullptr || bh == nullptr || ch == nullptr || dh == nullptr ||eh == nullptr || fh == nullptr ||
        gh == nullptr || hh == nullptr || ih == nullptr || jh == nullptr || kh == nullptr || lh == nullptr || mh == nullptr ||
        nh == nullptr || oh == nullptr || ph == nullptr || qh == nullptr || rh == nullptr || sh == nullptr || th == nullptr ||
        vh == nullptr || wh == nullptr || xh == nullptr || yh == nullptr || zh == nullptr ) {
        cout << "IMAGE CAN'T BE LOADED" << SDL_GetError() << endl;
        isRunning = false;
    }

    while (isRunning) {
        Uint32 startTicks = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                } else if (e.key.keysym.sym == SDLK_a) {
                    loadPoint(ah, boxpoint, aBoxes);
                    boxpoint.x+= (boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_b) {
                    loadPoint(bh, boxpoint, bBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_c) {
                    loadPoint(ch, boxpoint, cBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_d) {
                    loadPoint(dh, boxpoint, dBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_e) {
                    loadPoint(eh, boxpoint, eBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_f) {
                    loadPoint(fh, boxpoint, fBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_g) {
                    loadPoint(gh, boxpoint, gBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_h) {
                    loadPoint(hh, boxpoint, hBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_i) {
                    loadPoint(ih, boxpoint, iBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_j) {
                    loadPoint(jh, boxpoint, jBoxes);
                    boxpoint.x+= (boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_k) {
                    loadPoint(kh, boxpoint, kBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_l) {
                    loadPoint(lh, boxpoint, lBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_m) {
                    loadPoint(mh, boxpoint, mBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_n) {
                    loadPoint(nh, boxpoint, nBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_o) {
                    loadPoint(oh, boxpoint, oBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_p) {
                    loadPoint(ph, boxpoint, pBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_q) {
                    loadPoint(qh, boxpoint, qBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_r) {
                    loadPoint(rh, boxpoint, rBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_s) {
                    loadPoint(sh, boxpoint, sBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_t) {
                    loadPoint(th, boxpoint, tBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_u) {
                    loadPoint(uh, boxpoint, uBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_v) {
                    loadPoint(vh, boxpoint, vBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_w) {
                    loadPoint(wh, boxpoint, wBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_x) {
                    loadPoint(xh, boxpoint, xBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_y) {
                    loadPoint(yh, boxpoint, yBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                } else if (e.key.keysym.sym == SDLK_z) {
                    loadPoint(zh, boxpoint, zBoxes);
                    boxpoint.x+=(boxpoint.w/2);
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, nullptr, nullptr);

        for (const auto& box : aBoxes) {
            SDL_RenderCopy(renderer, ah, nullptr, &box);
        }

        for (const auto& box : bBoxes) {
            SDL_RenderCopy(renderer, bh, nullptr, &box);
        }

        for (const auto& box : cBoxes) {
            SDL_RenderCopy(renderer, ch, nullptr, &box);
        }

        for (const auto& box : dBoxes) {
            SDL_RenderCopy(renderer, dh, nullptr, &box);
        }

        for (const auto& box : eBoxes) {
            SDL_RenderCopy(renderer, eh, nullptr, &box);
        }

        for (const auto& box : fBoxes) {
            SDL_RenderCopy(renderer, fh, nullptr, &box);
        }

        for (const auto& box : gBoxes) {
            SDL_RenderCopy(renderer, gh, nullptr, &box);
        }

        for (const auto& box : hBoxes) {
            SDL_RenderCopy(renderer, hh, nullptr, &box);
        }

        for (const auto& box : iBoxes) {
            SDL_RenderCopy(renderer, ih, nullptr, &box);
        }

        for (const auto& box : jBoxes) {
            SDL_RenderCopy(renderer, jh, nullptr, &box);
        }

        for (const auto& box : kBoxes) {
            SDL_RenderCopy(renderer, kh, nullptr, &box);
        }

        for (const auto& box : lBoxes) {
            SDL_RenderCopy(renderer, lh, nullptr, &box);
        }

        for (const auto& box : mBoxes) {
            SDL_RenderCopy(renderer, mh, nullptr, &box);
        }

        for (const auto& box : nBoxes) {
            SDL_RenderCopy(renderer, nh, nullptr, &box);
        }

        for (const auto& box : oBoxes) {
            SDL_RenderCopy(renderer, oh, nullptr, &box);
        }

        for (const auto& box : pBoxes) {
            SDL_RenderCopy(renderer, ph, nullptr, &box);
        }

        for (const auto& box : qBoxes) {
            SDL_RenderCopy(renderer, qh, nullptr, &box);
        }

        for (const auto& box : rBoxes) {
            SDL_RenderCopy(renderer, rh, nullptr, &box);
        }

        for (const auto& box : sBoxes) {
            SDL_RenderCopy(renderer, sh, nullptr, &box);
        }

        for (const auto& box : tBoxes) {
            SDL_RenderCopy(renderer, th, nullptr, &box);
        }

        for (const auto& box : uBoxes) {
            SDL_RenderCopy(renderer, uh, nullptr, &box);
        }

        for (const auto& box : vBoxes) {
            SDL_RenderCopy(renderer, vh, nullptr, &box);
        }

        for (const auto& box : wBoxes) {
            SDL_RenderCopy(renderer, wh, nullptr, &box);
        }

        for (const auto& box : xBoxes) {
            SDL_RenderCopy(renderer, xh, nullptr, &box);
        }

        for (const auto& box : yBoxes) {
            SDL_RenderCopy(renderer, yh, nullptr, &box);
        }

        for (const auto& box : zBoxes) {
            SDL_RenderCopy(renderer, zh, nullptr, &box);
        }
        SDL_RenderPresent(renderer);
        capFrameRate(startTicks);
    }

    SDL_DestroyTexture(bg);

    quitSDL();

    return 0;
}
