#include "Renderer.hpp"
#include <stdexcept>
#include <SDL2/SDL_image.h>

#include <iostream>

Renderer::Renderer(int width, int height, const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("SDL init failed");

    _window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!_window)
        throw std::runtime_error("Window creation failed");

    _renderer = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!_renderer)
        throw std::runtime_error("Renderer creation failed");
}

Renderer::~Renderer()
{
    for (auto& [_, texture] : _textures)
        SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Renderer::beginFrame()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void Renderer::endFrame()
{
    SDL_RenderPresent(_renderer);
}

TextureID Renderer::loadTexture(const std::string& path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
        throw std::runtime_error("Failed to load texture");

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(_renderer, surface);

    SDL_FreeSurface(surface);

    if (!texture)
        throw std::runtime_error("Texture creation failed");

    TextureID id = _nextTextureID++;
    _textures[id] = texture;

    return id;
}

void Renderer::draw(
    TextureID textureID,
    const Vec2& position,
    float rotation,
    const Vec2& scale,
    int width,
    int height
)
{
    SDL_Texture* texture = _textures.at(textureID);

    SDL_Rect dst;
    dst.x = static_cast<int>(position.x);
    dst.y = static_cast<int>(position.y);
    dst.w = static_cast<int>(width * scale.x);
    dst.h = static_cast<int>(height * scale.y);

    SDL_RenderCopyEx(
        _renderer,
        texture,
        nullptr,
        &dst,
        rotation,
        nullptr,
        SDL_FLIP_NONE
    );
}
