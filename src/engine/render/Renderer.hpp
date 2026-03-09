#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

#include "engine/IRenderer.hpp"

class Renderer: public IRenderer
{
public:
    Renderer(int width, int height, const char *title = "Game");
    ~Renderer();

    void beginFrame() override;
    void endFrame() override;

    TextureID loadTexture(const std::string& path) override;

    void draw(
        TextureID texture,
        const Vec2& position,
        float rotation,
        const Vec2& scale,
        int width,
        int height
    ) override;

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    std::unordered_map<TextureID, SDL_Texture*> _textures;
    TextureID _nextTextureID = 0;
};
