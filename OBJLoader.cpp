#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

bool OBJLoader::LoadOBJ(
    const std::string& path,
    std::vector<OBJVertex>& out_vertices,
    std::vector<GLuint>& out_indices,
    std::vector<Texture>& out_textures)
{
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec2> temp_texcoords;
    std::vector<glm::vec3> temp_normals;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") { // Vertex position
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;
            temp_positions.push_back(position);
        }
        else if (type == "vt") { // Texture coordinate
            glm::vec2 texcoord;
            iss >> texcoord.x >> texcoord.y;
            texcoord.y = 1.0f - texcoord.y; // Flip Y for OpenGL
            temp_texcoords.push_back(texcoord);
        }
        else if (type == "vn") { // Vertex normal
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (type == "f") { // Face
            std::string vertexData;
            while (iss >> vertexData) {
                ProcessVertex(temp_positions, temp_texcoords, temp_normals,
                    vertexData, out_vertices, out_indices);
            }
        }
        // You can add mtl loading here if needed
    }

    return true;
}

void OBJLoader::ProcessVertex(
    const std::vector<glm::vec3>& temp_positions,
    const std::vector<glm::vec2>& temp_texcoords,
    const std::vector<glm::vec3>& temp_normals,
    const std::string& vertexData,
    std::vector<OBJVertex>& vertices,
    std::vector<GLuint>& indices)
{
    std::istringstream viss(vertexData);
    std::string posStr, texStr, normStr;

    std::getline(viss, posStr, '/');
    std::getline(viss, texStr, '/');
    std::getline(viss, normStr, '/');

    int posIdx = std::stoi(posStr) - 1;
    int texIdx = texStr.empty() ? -1 : std::stoi(texStr) - 1;
    int normIdx = normStr.empty() ? -1 : std::stoi(normStr) - 1;

    OBJVertex vertex;
    vertex.Position = temp_positions[posIdx];
    vertex.TexCoords = texIdx >= 0 ? temp_texcoords[texIdx] : glm::vec2(0.0f);
    vertex.Normal = normIdx >= 0 ? temp_normals[normIdx] : glm::vec3(0.0f, 1.0f, 0.0f);

    vertices.push_back(vertex);
    indices.push_back(vertices.size() - 1);
}