#pragma once

#include <string>

using TextureID = unsigned int;

struct Vec2 {
    float x = 0;
    float y = 0;
};

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;

    virtual TextureID loadTexture(const std::string& path) = 0;

    virtual void draw(
        TextureID texture,
        const Vec2& position,
        float rotation,
        const Vec2& scale,
        int width,
        int height
    ) = 0;
};
