
#include "../include/Hamster.h"
int Hamster::getVX() const {
    extern int g_vx;
    return g_vx;
}

// Stato movimento per gestione input e fisica
int g_vx = 0;
namespace {
    bool g_is_jumping = false;
    int g_jump_velocity = 0;
    const int g_max_vx_ground = 5;
    const int g_max_vx_air = 5;
    const int g_jump_strength = 23;
    const int g_gravity = 2;
}
void Hamster::updatePhysics(bool on_platform, int ground_y, const PlatformSet* platforms) {
    if (g_is_jumping) {
        move(g_vx, g_jump_velocity); // move() now updates m_prev_y for vertical movement
        g_jump_velocity += g_gravity;
        // Check landing on platform (only when falling)
        if (g_jump_velocity > 0 && platforms) {
            const Platform* plat = platforms->getLandingPlatform(x(), y(), size(), m_prev_y);
            if (plat) {
                int hy = y() + size();
                move(0, plat->y - hy); // Snap to platform
                g_is_jumping = false;
                g_jump_velocity = 0;
                return;
            }
        }
        // Check landing on ground
        if (y() >= ground_y) {
            move(0, ground_y - y());
            g_is_jumping = false;
            g_jump_velocity = 0;
        }
    } else {
        // If not on platform and not on ground, start falling
        if (!on_platform && y() < ground_y) {
            g_is_jumping = true;
            g_jump_velocity = 0;
        } else if (g_vx != 0) {
            move(g_vx, 0);
        }
    }
}
void Hamster::processKeys(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                m_facing_left = true;
                g_vx = g_is_jumping ? -g_max_vx_air : -g_max_vx_ground;
                if (!g_is_jumping) move(g_vx, 0);
                break;
            case SDLK_RIGHT:
                m_facing_left = false;
                g_vx = g_is_jumping ? g_max_vx_air : g_max_vx_ground;
                if (!g_is_jumping) move(g_vx, 0);
                break;
            case SDLK_UP:
                if (!g_is_jumping) {
                    g_is_jumping = true;
                    g_jump_velocity = -g_jump_strength;
                }
                break;
            default: break;
        }
    }
    if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {
            g_vx = 0;
        }
    }
}
#include "../include/Hamster.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Hamster::Hamster(int x, int y, int size, SDL_Renderer* renderer, const std::string& basePath)
    : m_x(x), m_y(y), m_size(size), m_prev_y(y)
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
    if (dy != 0) {
        m_prev_y = m_y;
        m_y += dy;
    }
    // Limita ai bordi della finestra
    if (m_x < 0) m_x = 0;
    if (m_x + m_size > 619) m_x = 619 - m_size;
    if (m_y < 0) m_y = 0;
    if (m_y + m_size > 598) m_y = 598 - m_size;
}

void Hamster::draw(SDL_Renderer* renderer) const {
    if (m_textures[m_frame]) {
        SDL_Rect dst = { m_x, m_y, m_size, m_size };
        SDL_RendererFlip flip = m_facing_left ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer, m_textures[m_frame], nullptr, &dst, 0, nullptr, flip);
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
