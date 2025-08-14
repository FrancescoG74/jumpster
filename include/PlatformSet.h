#pragma once
#include <vector>
#include <SDL2/SDL.h>

struct Platform {
    int x, y, w, h;
};

class PlatformSet {
public:
    PlatformSet();
    void draw(SDL_Renderer* renderer) const;
    bool isOnPlatform(int hamster_x, int hamster_y, int hamster_size) const;
    // Restituisce la piattaforma su cui il criceto atterra, nullptr se nessuna
    const Platform* getLandingPlatform(int hamster_x, int hamster_y, int hamster_size) const;
private:
    std::vector<Platform> m_platforms;
};
