

#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

struct Vertex {
   glm::vec3 Position;
   glm::vec3 Normal;
   glm::vec2 UV;
   };


#endif

#ifndef MESH_H
#define MESH_H

class Mesh {
public:
   std::vector<Vertex> vertices;
   std::vector<unsigned int> indices;
   GLuint VAO;

   Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
   void Draw();

private:
   GLuint VBO, EBO;
   void setupMesh();
   };

#endif