#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Texture.h"

class Model {
public:
    // OBJ loader constructor
    Model(const std::string& objPath, const std::string& texturePath = "");

    void Draw(Shader& shader, Camera& camera);

private:
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;

    // Helper functions for OBJ loading
    bool loadOBJ(const std::string& path,
        std::vector<Vertex>& vertices,
        std::vector<GLuint>& indices);
};