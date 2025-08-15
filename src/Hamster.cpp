#include "../include/Hamster.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Hamster::Hamster(int x, int y, int size, SDL_Renderer* renderer, const std::string& basePath)
    : m_x(x), m_y(y), m_size(size)
{
    // Carica 8 frame da mario00.png ... mario07.png
    for (int i = 0; i < 8; ++i) {
        char filename[128];
        snprintf(filename, sizeof(filename), "%s%02d.png", basePath.c_str(), i);
        SDL_Surface* surface = IMG_Load(filename);
        if (!surface) {
            std::cerr << "IMG_Load failed: " << filename << " " << IMG_GetError() << std::endl;
            m_textures[i] = nullptr;
        } else {
            m_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            if (!m_textures[i]) {
                std::cerr << "SDL_CreateTextureFromSurface failed: " << filename << " " << SDL_GetError() << std::endl;
            }
        }
    }
}

Hamster::~Hamster() {
    for (int i = 0; i < 8; ++i) {
        if (m_textures[i]) SDL_DestroyTexture(m_textures[i]);
    }
}

void Hamster::move(int dx, int dy) {
    m_x += dx;
    m_y += dy;
    // Limita ai bordi della finestra
    if (m_x < 0) m_x = 0;
    if (m_x + m_size > 619) m_x = 619 - m_size;
    if (m_y < 0) m_y = 0;
    if (m_y + m_size > 598) m_y = 598 - m_size;
}

void Hamster::draw(SDL_Renderer* renderer) const {
    if (m_textures[m_frame]) {
        SDL_Rect dst = { m_x, m_y, m_size, m_size };
        SDL_RenderCopy(renderer, m_textures[m_frame], nullptr, &dst);
    }
}

void Hamster::stepAnimation(int vx) {
    if (vx != 0) {
        m_animCounter++;
        if (m_animCounter >= m_animSpeed) {
            m_animCounter = 0;
            m_frame = (m_frame + 1) % m_frameCount;
        }
    } else {
        m_frame = 0; // fermo: primo frame
        m_animCounter = 0;
    }
}

int Hamster::x() const { return m_x; }
int Hamster::y() const { return m_y; }
int Hamster::size() const { return m_size; }
