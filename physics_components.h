#pragma once
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"shaderClass.h"
#include"linear_algebra.h"

struct PhysicsComponent {
    glm::vec3 velocity;
    glm::vec3 eulerVelocity;
};