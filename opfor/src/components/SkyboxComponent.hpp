#pragma once

#include <opfor/ecs/Component.hpp>

namespace opfor
{

struct SkyboxComponent : ecs::IComponentBase
{
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint texture = 0;
};

} // namespace opfor
