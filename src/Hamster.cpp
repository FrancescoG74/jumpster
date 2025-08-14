#include "../include/Hamster.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Hamster::Hamster(int x, int y, int size, SDL_Renderer* renderer, const std::string& imagePath)
    : m_x(x), m_y(y), m_size(size), m_texture(nullptr)
{
    // Il path deve essere relativo alla directory resources
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        std::cerr << "IMG_Load failed: " << IMG_GetError() << std::endl;
        return;
    }
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!m_texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }

    // Calcola dimensioni frame
    int texW = 0, texH = 0;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &texW, &texH);
    m_frameW = texW / m_frameCount;
    m_frameH = texH;
}

Hamster::~Hamster() {
    if (m_texture) SDL_DestroyTexture(m_texture);
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
    if (m_texture) {
        // Avanza frame animazione
        Hamster* self = const_cast<Hamster*>(this);
        self->m_animCounter++;
        if (self->m_animCounter >= m_animSpeed) {
            self->m_animCounter = 0;
            self->m_frame = (self->m_frame + 1) % m_frameCount;
        }
        SDL_Rect src = { m_frame * m_frameW, 0, m_frameW, m_frameH };
        SDL_Rect dst = { m_x, m_y, m_size, m_size };
        SDL_RenderCopy(renderer, m_texture, &src, &dst);
    }
}

int Hamster::x() const { return m_x; }
int Hamster::y() const { return m_y; }
int Hamster::size() const { return m_size; }
