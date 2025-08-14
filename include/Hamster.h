#pragma once
#include <SDL2/SDL.h>
#include <string>

class Hamster {
public:
    Hamster(int x, int y, int size, SDL_Renderer* renderer, const std::string& imagePath);
    ~Hamster();
    void move(int dx, int dy);
    void draw(SDL_Renderer* renderer) const;
    int x() const;
    int y() const;
    int size() const;
private:
    int m_x, m_y, m_size;
    SDL_Texture* m_texture;
    int m_frame = 0;
    int m_frameCount = 16;
    int m_frameW = 0;
    int m_frameH = 0;
    int m_animCounter = 0;
    int m_animSpeed = 6; // frame avanzato ogni 6 draw
};
