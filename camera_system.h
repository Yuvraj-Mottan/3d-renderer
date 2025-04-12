#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"linear_algebra.h"
#include"shaderClass.h"

#include "camera_components.h"
#include "transform_components.h"
#include<unordered_map>

class CameraSystem {
public:

    CameraSystem(unsigned int shader, GLFWwindow* window);

    bool update(
        std::unordered_map<unsigned int, TransformComponent>& transformComponents,
        unsigned int cameraID, CameraComponent& cameraComponent, float dt);

private:
    unsigned int viewLocation;
    glm::vec3 global_up = { 0.0f, 0.0f, 1.0f };
    GLFWwindow* window;
};