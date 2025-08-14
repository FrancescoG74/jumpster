#pragma once
#include <SDL2/SDL.h>
#include <string>

class Background {
public:
    Background(int width, int height, SDL_Renderer* renderer, const std::string& imagePath);
    ~Background();
    void draw(SDL_Renderer* renderer) const;
private:
    int m_width, m_height;
    int m_imgW, m_imgH;
    SDL_Texture* m_texture;
};
