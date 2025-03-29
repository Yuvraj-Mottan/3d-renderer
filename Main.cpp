#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include"Material.h"
#include "triangle_mesh.h"
#include"Maths.h"

using namespace std;

const unsigned int width = 1000, height = 800;

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with correct dimensions
    GLFWwindow* window = glfwCreateWindow(width, height, "3D Renderer Window", NULL, NULL);
    if (!window) {
        cout << "Window cannot be opened" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load GLAD
    gladLoadGL();

    // Set viewport correctly
    glViewport(0, 0, width, height);

    // Shader program
    Shader shaderPrg("default.vert", "default.frag");
    shaderPrg.activate();  // Activate before setting uniforms
   
    glUniform1i(glGetUniformLocation(shaderPrg.ID, "material"),0);
    glUniform1i(glGetUniformLocation(shaderPrg.ID, "mask"), 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    TriangleMesh* triangle = new TriangleMesh();
    Material* material = new Material("D:\\Projects\\3d renderer\\3d renderer\\Img.jpeg");
    Material* mask = new Material("D:\\Projects\\mask.jpeg");

    
    vec3 quad_position = { 0.4f,-0.2f,0.0f };
    vec3 camera_position = { -5.0f,0.0f,3.0f };
    vec3 camera_target = { 0.0f,0.0f,0.0f };
    unsigned int model_location = glGetUniformLocation(shaderPrg.ID, "model");
    unsigned int view_location = glGetUniformLocation(shaderPrg.ID, "view");
    unsigned int projection_location = glGetUniformLocation(shaderPrg.ID, "projection");

    mat4 projection = createProjection(45.0f, 640.0f/480.0f, 0.1f, 10.0f);
    mat4 view = lookAt(camera_position, camera_target);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, view.m);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.m);
     

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        mat4 model = createModelMatrix(quad_position,10 * glfwGetTime());   
        glUniformMatrix4fv(model_location, 1, GL_FALSE, model.m);

        glClear(GL_COLOR_BUFFER_BIT);

        // Activate shader and bind VAO
        shaderPrg.activate();
        material->use(0);
        mask->use(1);

        triangle->draw();
        glfwSwapBuffers(window);
    }

    delete material;
    delete mask;

    shaderPrg.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
