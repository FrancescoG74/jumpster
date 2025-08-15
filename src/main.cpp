#include "../include/PlatformSet.h"

#include <SDL2/SDL.h>
#include <iostream>
#include "../include/Hamster.h"
#include "../include/Background.h"
#include <SDL2/SDL_image.h>

const int WINDOW_WIDTH = 619;
const int WINDOW_HEIGHT = 598;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Criceto!", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Posiziona il criceto in basso a sinistra
    int hamster_size = 40;
    int ground_y = WINDOW_HEIGHT - hamster_size; // base della finestra
    Hamster hamster(0, ground_y, hamster_size, renderer, "../resources/mario");
    PlatformSet platforms;
    bool is_jumping = false;
    int jump_velocity = 0;
    int vx = 0; // velocità orizzontale
    const int max_vx_ground = 5;
    const int max_vx_air = 5;
    const int jump_strength = 23;
    const int gravity = 2;
    Background background(WINDOW_WIDTH, WINDOW_HEIGHT, renderer, "../resources/background_platform.png");
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // Aggiorna stato piattaforma DOPO ogni movimento
        bool on_platform = platforms.isOnPlatform(hamster.x(), hamster.y(), hamster.size());
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        vx = is_jumping ? -max_vx_air : -max_vx_ground;
                        if (!is_jumping) hamster.move(vx, 0);
                        break;
                    case SDLK_RIGHT:
                        vx = is_jumping ? max_vx_air : max_vx_ground;
                        if (!is_jumping) hamster.move(vx, 0);
                        break;
                    case SDLK_UP:
                            if (!is_jumping && (hamster.y() >= ground_y || on_platform)) {
                                is_jumping = true;
                                jump_velocity = -jump_strength;
                            }
                        break;
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_q: quit = true; break;
                }
            }
            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {
                    vx = 0;
                }
            }
        }

        // Logica salto e gravità con piattaforme
        if (is_jumping) {
            hamster.move(vx, jump_velocity);
            jump_velocity += gravity;
            // Aggiorna stato piattaforma dopo il movimento verticale
            on_platform = platforms.isOnPlatform(hamster.x(), hamster.y(), hamster.size());
            // Atterra su piattaforma
            if (on_platform && jump_velocity > 0) {
                // Allinea il criceto sopra la piattaforma
                const Platform* plat = platforms.getLandingPlatform(hamster.x(), hamster.y(), hamster.size());
                if (plat) {
                    int hy = hamster.y() + hamster.size();
                    hamster.move(0, plat->y - hy);
                }
                is_jumping = false;
            } else if (hamster.y() >= ground_y) {
                hamster.move(0, ground_y - hamster.y()); // correggi posizione
                is_jumping = false;
            }
        } else {
            on_platform = platforms.isOnPlatform(hamster.x(), hamster.y(), hamster.size());
            if (!on_platform && hamster.y() < ground_y) {
                // Se non è su piattaforma e non a terra, cade
                is_jumping = true;
                jump_velocity = 0;
            } else if (vx != 0) {
                hamster.move(vx, 0);
            }
        }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    background.draw(renderer);
    platforms.draw(renderer);
    hamster.stepAnimation(vx);
    hamster.draw(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 FPS
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
