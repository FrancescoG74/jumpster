#include "../include/PlatformSet.h"
const Platform* PlatformSet::getLandingPlatform(int hamster_x, int hamster_y, int hamster_size) const {
    int hx = hamster_x;
    int hy = hamster_y + hamster_size;
    for (const auto& p : m_platforms) {
        if (hy >= p.y && hy <= p.y + p.h) {
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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 80, 200, 80, 0); // trasparente
    for (const auto& p : m_platforms) {
        SDL_Rect rect = {p.x, p.y, p.w, p.h};
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool PlatformSet::isOnPlatform(int hamster_x, int hamster_y, int hamster_size) const {
    // Controlla se il bordo inferiore del criceto tocca una piattaforma
    int hx = hamster_x;
    int hy = hamster_y + hamster_size;
    for (const auto& p : m_platforms) {
        if (hy >= p.y && hy <= p.y + p.h) {
            if (hx + hamster_size > p.x && hx < p.x + p.w) {
                return true;
            }
        }
    }
    return false;
}
