#include "../include/Treasure.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Treasure::Treasure(int x, int y, int w, int h, SDL_Renderer* renderer, const std::string& imagePath)
    : m_x(x), m_y(y), m_w(w), m_h(h)
{
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        std::cerr << "IMG_Load failed: " << imagePath << " " << IMG_GetError() << std::endl;
        m_texture = nullptr;
    } else {
        m_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!m_texture) {
            std::cerr << "SDL_CreateTextureFromSurface failed: " << imagePath << " " << SDL_GetError() << std::endl;
        }
    }
}

Treasure::~Treasure() {
    if (m_texture) SDL_DestroyTexture(m_texture);
}

void Treasure::draw(SDL_Renderer* renderer) const {
    if (m_texture) {
        SDL_Rect dst = { m_x, m_y, m_w, m_h };
        SDL_RenderCopy(renderer, m_texture, nullptr, &dst);
    }
}
