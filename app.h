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
#include "physics_components.h"
#include "render_components.h"
#include "transform_components.h"

#include "camera_system.h"
#include "motion_system.h"
#include "render_system.h"

#include "shaderClass.h"

class App {
public:
    App();
    ~App();
    void run();
    unsigned int make_entity();
    unsigned int make_cube_mesh(glm::vec3 size);
    unsigned int make_texture(const char* filename);
    void set_up_opengl();
    void make_systems();

    //Components
    std::unordered_map<unsigned int, TransformComponent> transformComponents;
    std::unordered_map<unsigned int, PhysicsComponent> physicsComponents;
    CameraComponent* cameraComponent;
    unsigned int cameraID;
    std::unordered_map<unsigned int, RenderComponent> renderComponents;

private:
    void set_up_glfw();

    unsigned int entity_count = 0;
    GLFWwindow* window;

    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> textures;

    unsigned int shader;

    //Systems
    MotionSystem* motionSystem;
    CameraSystem* cameraSystem;
    RenderSystem* renderSystem;
};