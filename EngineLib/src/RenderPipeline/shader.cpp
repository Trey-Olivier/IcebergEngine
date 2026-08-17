//
// Created by treyo on 8/16/2026.
//
#include "RenderPipeline\shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>

using std::ifstream;
using std::stringstream;
using std::cout;

namespace {

    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                spdlog::error("SHADER_COMPILATION_ERROR of type: {}\n{}\n{}", type, infoLog, std::string(51, '-'));
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                spdlog::error("PROGRAM_LINKING_ERROR of type: {}\n{}", type, infoLog);
            }
        }
    }

}

namespace RenderPipeline {

    shader::shader(string vPath, string fPath) : vertPath(vPath), fragPath(fPath)
    {
        compileShaders();
    }
    void shader::bind()
    {
        glUseProgram(program);
    }
    void shader::setMat4(string name, mat4 mat)
    {
        GLint location = glGetUniformLocation(program, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }
    string shader::readFile(const string& path)
    {
        string code;
        ifstream file;

        file.exceptions(ifstream::failbit | ifstream::badbit);
        try
        {
            file.open(path);
            stringstream stream;
            stream << file.rdbuf();
            file.close();
            return stream.str();
        }
        catch (ifstream::failure& e)
        {
            stringstream ss{ "Shader file " };
            ss << path << " failed to open";
            spdlog::error(ss.str());
        }

        return string();
    }
    void shader::compileShaders() {
        string vertCode = readFile(vertPath);
        string fragCode = readFile(fragPath);

        const char* code = vertCode.c_str();

        u32 v, f;
        v = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(v, 1, &code, NULL);
        glCompileShader(v);
        checkCompileErrors(v, "VERTEX");

        f = glCreateShader(GL_FRAGMENT_SHADER);
        code = fragCode.c_str();
        glShaderSource(f, 1, &code, NULL);
        glCompileShader(f);
        checkCompileErrors(f, "FRAGMENT");

        program = glCreateProgram();
        glAttachShader(program, v);
        glAttachShader(program, f);
        glLinkProgram(program);
        checkCompileErrors(program, "PROGRAM");

        glDeleteShader(v);
        glDeleteShader(f);
    }
}