//
// Created by treyo on 8/16/2026.
//

#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

using std::string;
using namespace glm;

namespace RenderPipeline
{
    class shader
    {
    public:
        shader() = default;
        ~shader()
        {
            if (program != 0)
                glDeleteProgram(program);
        }
        shader(string vertPath, string fragPath);
        void bind();
        void setMat4(string, mat4);
    private:
        string readFile(const string& path);
        void compileShaders();
        string vertPath, fragPath;
        u32 program{};
    };
}