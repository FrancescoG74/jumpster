#ifdef __cplusplus
extern "C" {
#endif
extern int g_vx;
#ifdef __cplusplus
}
#endif

#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Actor.h"
#include "PlatformSet.h"

class Hamster : public Actor {
public:
    Hamster(int x, int y, int size, SDL_Renderer* renderer, const std::string& basePath = "../resources/mario");
    ~Hamster();
    void move(int dx, int dy);
    void draw(SDL_Renderer* renderer) const override;
    void stepAnimation(int vx);
    int x() const;
    int y() const;
    int size() const;
    void processKeys(const SDL_Event& e) override;
    void updatePhysics(bool on_platform, int ground_y, const PlatformSet* platforms);
    int getVX() const;
private:
    int m_x, m_y, m_size;
    int m_prev_y;
    SDL_Texture* m_textures[8] = {nullptr};
    int m_frame = 0;
    int m_frameCount = 8;
    int m_animCounter = 0;
    int m_animSpeed = 6; // frame avanzato ogni 6 draw
    bool m_facing_left = false;
};
