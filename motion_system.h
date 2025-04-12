#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"linear_algebra.h"
#include "transform_components.h"
#include "physics_components.h"
#include<unordered_map>
class MotionSystem {
public:

    void update(
        std::unordered_map<unsigned int, TransformComponent>& transformComponents,
        std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
        float dt);
};