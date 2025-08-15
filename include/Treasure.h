#pragma once
#include "Actor.h"
#include <SDL2/SDL.h>
#include <string>

class Treasure : public Actor {
public:
    Treasure(int x, int y, int w, int h, SDL_Renderer* renderer, const std::string& imagePath);
    ~Treasure();
    void draw(SDL_Renderer* renderer) const override;
    int x() const { return m_x; }
    int y() const { return m_y; }
    int width() const { return m_w; }
    int height() const { return m_h; }
private:
    int m_x, m_y, m_w, m_h;
    SDL_Texture* m_texture = nullptr;
};
