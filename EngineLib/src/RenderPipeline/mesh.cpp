//
// Created by treyo on 8/17/2026.
//
#include "RenderPipeline/mesh.h"

#include <glad/glad.h>

namespace RenderPipeline {
    mesh::mesh(const std::vector<vertex> &vertices, const std::vector<unsigned int> &indices) {
        indexCount = indices.size();
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    mesh::~mesh() {
        cleanup();
    }

    mesh::mesh(mesh &&other) noexcept
        : VAO(other.VAO), VBO(other.VBO), EBO(other.EBO), indexCount(other.indexCount){
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
        other.indexCount = 0;
    }

    mesh & mesh::operator=(mesh &&other) noexcept {
        if (this != &other) {
            cleanup();
            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;
            indexCount = other.indexCount;

            other.VAO = 0;
            other.VBO = 0;
            other.EBO = 0;
            other.indexCount = 0;
        }
        return *this;
    }

    void mesh::bind() const {
        glBindVertexArray(VAO);
    }

    void mesh::cleanup() noexcept {
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
        if (EBO) glDeleteBuffers(1, &EBO);
    }
}
