#include "../include/Background.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Background::Background(int width, int height, SDL_Renderer* renderer, const std::string& imagePath)
    : m_width(width), m_height(height), m_imgW(0), m_imgH(0), m_texture(nullptr)
{
    // Il path PNG deve essere relativo a ../resources
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        std::cerr << "IMG_Load failed: " << IMG_GetError() << std::endl;
        return;
    }
    m_imgW = surface->w;
    m_imgH = surface->h;
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!m_texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }
}

Background::~Background() {
    if (m_texture) SDL_DestroyTexture(m_texture);
}

void Background::draw(SDL_Renderer* renderer) const {
    if (m_texture) {
        int x = (m_width - m_imgW) / 2;
        int y = (m_height - m_imgH) / 2;
        SDL_Rect dst = { x, y, m_imgW, m_imgH };
        SDL_RenderCopy(renderer, m_texture, nullptr, &dst);
    }
}
