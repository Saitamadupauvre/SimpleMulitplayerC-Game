#pragma once

namespace GameConfig
{
namespace Window {
constexpr int Width = 800;
constexpr int Height = 600;
}

namespace Player {
constexpr int SpriteSize = 64;
}

namespace Duel {
constexpr int LeftSpawnX = Window::Width / 4;
constexpr int RightSpawnX = (Window::Width * 3) / 4;
constexpr int SpawnY = Window::Height / 2;
}

} // namespace GameConfig
