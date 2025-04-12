#include "Model.h"
#include "shaderClass.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main() {
    // Initialize GLFW and window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "OBJ Renderer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);

    // Create shader and enable depth testing
    Shader shader("default.vert", "default.frag");
    glEnable(GL_DEPTH_TEST);

    // Setup camera
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));

    // Load OBJ model (with optional texture)
    Model model("cube2.txt");
    // Model model("model.obj"); // Without texture

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        model.Draw(shader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}