#pragma once
#include <SDL2/SDL.h>
#include "Hamster.h"
#include "PlatformSet.h"
#include "Background.h"
#include "Treasure.h"

class JumpsterApp {
public:
    JumpsterApp();
    ~JumpsterApp();
    int run();
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Hamster* hamster = nullptr;
    PlatformSet* platforms = nullptr;
    class Treasure* treasure = nullptr;
    Background* background = nullptr;
    int hamster_size = 40;
    int ground_y = 0;
    bool is_jumping = false;
    int jump_velocity = 0;
    int vx = 0;
    const int max_vx_ground = 5;
    const int max_vx_air = 5;
    const int jump_strength = 23;
    const int gravity = 2;
    bool quit = false;
    void cleanup();
};
