#pragma once
#include <SDL2/SDL.h>

class Actor {
public:
    virtual ~Actor() = default;
    virtual void draw(SDL_Renderer* renderer) const = 0;
    virtual void processKeys(const SDL_Event& e) {}
};
