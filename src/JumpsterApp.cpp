#include "../include/JumpsterApp.h"
#include <SDL2/SDL_image.h>
#include <iostream>

const int WINDOW_WIDTH = 619;
const int WINDOW_HEIGHT = 598;

JumpsterApp::JumpsterApp() {
    // ...esistente init SDL, window, renderer...
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow("Jumpster", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    background = new Background(WINDOW_WIDTH, WINDOW_HEIGHT, renderer, "../resources/background_platform.png");
    // Tesoro 40x32 px sopra la piattaforma {1, 358, 35, 20}
    int treasure_w = 40;
    int treasure_h = 32;
    int plat_x = 1, plat_y = 358, plat_w = 35;
    int treasure_x = plat_x + (plat_w - treasure_w) / 2;
    int treasure_y = plat_y - treasure_h;
    treasure = new Treasure(treasure_x, treasure_y, treasure_w, treasure_h, renderer, "../resources/treasure_40x30.png");
    hamster_size = 40;
    ground_y = WINDOW_HEIGHT - hamster_size;
    hamster = new Hamster(0, ground_y, hamster_size, renderer, "../resources/mario");
    platforms = new PlatformSet();
}

JumpsterApp::~JumpsterApp() {
    cleanup();
}

void JumpsterApp::cleanup() {
    if (hamster) delete hamster;
    if (platforms) delete platforms;
    if (background) delete background;
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int JumpsterApp::run() {
    if (!window || !renderer || !hamster || !platforms || !background) return 1;
    SDL_Event e;
    int prev_y = hamster->y();
    auto checkTreasureCollision = [](const Hamster* h, const Treasure* t) {
        if (!h || !t) return false;
        int hx = h->x(), hy = h->y(), hs = h->size();
        int tx = t->x(), ty = t->y(), tw = t->width(), th = t->height();
        return (hx < tx + tw && hx + hs > tx && hy < ty + th && hy + hs > ty);
    };
    bool treasure_collected = false;
    bool win_dialog_shown = false;
    while (!quit) {
        prev_y = hamster->y();
        bool on_platform = platforms->isOnPlatform(hamster->x(), hamster->y(), hamster->size(), prev_y);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)) {
                quit = true;
            }
            hamster->processKeys(e);
        }
        hamster->updatePhysics(on_platform, ground_y, platforms);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        background->draw(renderer);
        platforms->draw(renderer);
        hamster->stepAnimation(hamster->getVX());
        hamster->draw(renderer);
        if (treasure && !treasure_collected) {
            treasure->draw(renderer);
            if (checkTreasureCollision(hamster, treasure)) {
                treasure_collected = true;
            }
        }
        if (treasure_collected && !win_dialog_shown) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hai vinto!", "Complimenti, hai raccolto il tesoro!", window);
            win_dialog_shown = true;
            quit = true;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    return 0;
}
