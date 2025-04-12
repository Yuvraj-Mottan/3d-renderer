#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Texture.h"

struct OBJVertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class OBJLoader {
public:
    static bool LoadOBJ(
        const std::string& path,
        std::vector<OBJVertex>& out_vertices,
        std::vector<GLuint>& out_indices,
        std::vector<Texture>& out_textures
    );

    static void ProcessVertex(
        const std::vector<glm::vec3>& temp_positions,
        const std::vector<glm::vec2>& temp_texcoords,
        const std::vector<glm::vec3>& temp_normals,
        const std::string& vertexData,
        std::vector<OBJVertex>& vertices,
        std::vector<GLuint>& indices
    );
};