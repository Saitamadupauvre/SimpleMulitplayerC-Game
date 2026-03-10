#include "Renderer.hpp"
#include <stdexcept>
#include <SDL2/SDL_image.h>
#include <string>

Renderer::Renderer(int width, int height, const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(std::string("SDL init failed: ") + SDL_GetError());

    const int imageFlags = IMG_INIT_PNG;
    if ((IMG_Init(imageFlags) & imageFlags) != imageFlags) {
        const std::string error = std::string("SDL_image init failed: ") + IMG_GetError();
        SDL_Quit();
        throw std::runtime_error(error);
    }

    _window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!_window)
    {
        const std::string error = std::string("Window creation failed: ") + SDL_GetError();
        IMG_Quit();
        SDL_Quit();
        throw std::runtime_error(error);
    }

    _renderer = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!_renderer)
    {
        const std::string error = std::string("Renderer creation failed: ") + SDL_GetError();
        SDL_DestroyWindow(_window);
        _window = nullptr;
        IMG_Quit();
        SDL_Quit();
        throw std::runtime_error(error);
    }
}

Renderer::~Renderer()
{
    for (auto& [_, texture] : _textures)
        SDL_DestroyTexture(texture);

    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);

    IMG_Quit();
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
        throw std::runtime_error(std::string("Failed to load texture: ") + IMG_GetError());

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(_renderer, surface);

    SDL_FreeSurface(surface);

    if (!texture)
        throw std::runtime_error(std::string("Texture creation failed: ") + SDL_GetError());

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
