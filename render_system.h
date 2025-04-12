#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"linear_algebra.h"
#include "transform_components.h"
#include "render_components.h"
#include<unordered_map>
class RenderSystem {
public:

    RenderSystem(unsigned int shader, GLFWwindow* window);

    void update(
        std::unordered_map<unsigned int, TransformComponent>& transformComponents,
        std::unordered_map<unsigned int, RenderComponent>& renderComponents);

private:

    unsigned int modelLocation;
    GLFWwindow* window;
};