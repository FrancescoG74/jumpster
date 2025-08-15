#pragma once
#include <SDL2/SDL.h>
#include <string>

class Hamster {
public:
    Hamster(int x, int y, int size, SDL_Renderer* renderer, const std::string& basePath = "../resources/mario");
    ~Hamster();
    void move(int dx, int dy);
    void draw(SDL_Renderer* renderer) const;
    void stepAnimation(int vx); // avanza animazione solo se vx != 0
    int x() const;
    int y() const;
    int size() const;
private:
    int m_x, m_y, m_size;
    SDL_Texture* m_textures[8] = {nullptr};
    int m_frame = 0;
    int m_frameCount = 8;
    int m_animCounter = 0;
    int m_animSpeed = 6; // frame avanzato ogni 6 draw
};
