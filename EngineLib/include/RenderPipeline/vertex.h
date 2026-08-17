//
// Created by treyo on 8/17/2026.
//

#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace RenderPipeline {

    struct vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

}

