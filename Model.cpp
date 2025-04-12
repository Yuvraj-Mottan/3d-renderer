#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>

Model::Model(const std::string& objPath, const std::string& texturePath) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    if (!loadOBJ(objPath, vertices, indices)) {
        std::cerr << "Failed to load OBJ model: " << objPath << std::endl;
        return;
    }

    // Load texture if specified
    std::vector<Texture> textures;
    if (!texturePath.empty()) {
        textures.emplace_back(texturePath.c_str(), "diffuse", 0);
    }

    // Create mesh from loaded data
    meshes.emplace_back(vertices, indices, textures);
}

bool Model::loadOBJ(const std::string& path,
    std::vector<Vertex>& vertices,
    std::vector<GLuint>& indices) {
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec2> temp_texcoords;
    std::vector<glm::vec3> temp_normals;

    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;
            temp_positions.push_back(position);
        }
        else if (type == "vt") {
            glm::vec2 texcoord;
            iss >> texcoord.x >> texcoord.y;
            texcoord.y = 1.0f - texcoord.y; // Flip Y for OpenGL
            temp_texcoords.push_back(texcoord);
        }
        else if (type == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (type == "f") {
            std::string vertexData;
            for (int i = 0; i < 3; i++) {
                iss >> vertexData;
                std::istringstream viss(vertexData);
                std::string posStr, texStr, normStr;

                std::getline(viss, posStr, '/');
                std::getline(viss, texStr, '/');
                std::getline(viss, normStr, '/');

                Vertex vertex;
                vertex.position = temp_positions[std::stoi(posStr) - 1];

                if (!texStr.empty())
                    vertex.texUV = temp_texcoords[std::stoi(texStr) - 1];

                if (!normStr.empty())
                    vertex.normal = temp_normals[std::stoi(normStr) - 1];
                else
                    vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f); // Default normal

                vertex.color = glm::vec3(1.0f); // White color
                vertices.push_back(vertex);
                indices.push_back(vertices.size() - 1);
            }
        }
    }
    return true;
}

void Model::Draw(Shader& shader, Camera& camera) {
    for (auto& mesh : meshes) {
        mesh.Draw(shader, camera);
    }
}