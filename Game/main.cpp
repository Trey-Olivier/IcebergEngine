
#include <glad/glad.h>          // must be included before glfw3.h
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "RenderPipeline/vertex.h"
#include "RenderPipeline/mesh.h"
#include "RenderPipeline/shader.h"


namespace {
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    float playerYaw   = -90.0f; // Renamed to avoid global collisions
    float playerPitch =  0.0f; // Renamed to avoid global collisions

    float lastX = 400.0f, lastY = 300.0f;
    bool  firstMouse = true;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    constexpr float sensitivity = 0.1f; // Made constexpr as requested
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    auto xpos = static_cast<float>(xposIn); // Using auto with static_cast
    auto ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    playerYaw   += xoffset;
    playerPitch += yoffset;

    if (playerPitch > 89.0f)  playerPitch = 89.0f;
    if (playerPitch < -89.0f) playerPitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(playerYaw)) * cos(glm::radians(playerPitch));
    direction.y = sin(glm::radians(playerPitch));
    direction.z = sin(glm::radians(playerYaw)) * cos(glm::radians(playerPitch));
    cameraFront = glm::normalize(direction);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// ----------------------------------------------------------------------------
// main
// ----------------------------------------------------------------------------
int main()
{
    // 1. GLFW + window + context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Replaced 0/NULL with nullptr
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Viewspace - Cleaned", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);

    // 2. GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // 3. Depth testing
    glEnable(GL_DEPTH_TEST);

    // 4. Create Mesh Data (Indexed Cube with position, normals, and UVs)
    std::vector<RenderPipeline::vertex> vertices = {
        // Front face
        { {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
        // Back face
        { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} },
        { {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} },
    };

    std::vector<unsigned int> indices = {
        // Front
        0, 1, 2,  2, 3, 0,
        // Right
        1, 5, 6,  6, 2, 1,
        // Back
        5, 4, 7,  7, 6, 5,
        // Left
        4, 0, 3,  3, 7, 4,
        // Bottom
        4, 5, 1,  1, 0, 4,
        // Top
        3, 2, 6,  6, 7, 3
    };

    RenderPipeline::mesh cubeMesh(vertices, indices);

    // 5. Load Shaders[cite: 5]
    RenderPipeline::shader cubeShader("E:/Repos/IcebergEngine/Game/assets/shaders/vertexShaderSrc.glsl", "E:/Repos/IcebergEngine/Game/assets/shaders/fragmentShaderSrc.glsl");

    // 6. Render loop
    while (!glfwWindowShouldClose(window))
    {
        auto currentFrame = static_cast<float>(glfwGetTime()); // Cast using auto
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(window);

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.bind(); //[cite: 5]

        auto model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        cubeShader.setMat4("model", model);       //[cite: 5]
        cubeShader.setMat4("view", view);         //[cite: 5]
        cubeShader.setMat4("projection", projection); //[cite: 5]

        cubeMesh.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(cubeMesh.GetIndexCount()), GL_UNSIGNED_INT, nullptr); // Replaced 0 with nullptr

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}