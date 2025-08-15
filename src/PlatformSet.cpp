#include "../include/PlatformSet.h"
// Migliorata: controlla se il bordo inferiore attraversa la piattaforma dall'alto
const Platform* PlatformSet::getLandingPlatform(int hamster_x, int hamster_y, int hamster_size, int prev_y) const {
    int hx = hamster_x;
    int hy = hamster_y + hamster_size;
    int prev_hy = prev_y + hamster_size;
    for (const auto& p : m_platforms) {
        // Solo se il bordo inferiore attraversa la piattaforma dall'alto
        if (prev_hy <= p.y && hy >= p.y && hy <= p.y + p.h) {
            if (hx + hamster_size > p.x && hx < p.x + p.w) {
                return &p;
            }
        }
    }
    return nullptr;
}
#include "../include/PlatformSet.h"

PlatformSet::PlatformSet() {
    // Piattaforme hardcoded (coordinate e dimensioni in pixel)
    m_platforms.push_back({232, 515, 100, 20});
    m_platforms.push_back({395, 550, 170, 20});
    m_platforms.push_back({525, 427, 95, 20});
    m_platforms.push_back({547, 298, 72, 20});
    m_platforms.push_back({465, 254, 72, 20});
    m_platforms.push_back({163, 222, 74, 20});
    m_platforms.push_back({132, 315, 41, 20});
    m_platforms.push_back({238, 327, 43, 10});
    m_platforms.push_back({1, 358, 35, 20});
    m_platforms.push_back({261, 251, 70, 30});
    m_platforms.push_back({379, 367, 60, 20});
    m_platforms.push_back({580, 161, 40, 20});

}

void PlatformSet::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 80, 200, 80, 255); // verde opaco
    for (const auto& p : m_platforms) {
        SDL_Rect rect = {p.x, p.y, p.w, p.h};
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Migliorata: true solo se il bordo inferiore è appena sopra la piattaforma
bool PlatformSet::isOnPlatform(int hamster_x, int hamster_y, int hamster_size, int prev_y) const {
    int hx = hamster_x;
    int hy = hamster_y + hamster_size;
    int prev_hy = prev_y + hamster_size;
    for (const auto& p : m_platforms) {
        if (prev_hy <= p.y && hy >= p.y && hy <= p.y + p.h) {
            if (hx + hamster_size > p.x && hx < p.x + p.w) {
                return true;
            }
        }
    }
    return false;
}
