#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include"Material.h"
#include "triangle_mesh.h"

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

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
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
