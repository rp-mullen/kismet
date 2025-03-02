// Material.h
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Material {
public:
   glm::vec3 color; // Object color
   glm::vec3 specular; // Specular color for highlights
   float shininess; // Shininess for specular reflection
   unsigned int textureID; // Texture ID for diffuse maps
   unsigned int normalMapID; // Texture ID for normal maps

   Material(glm::vec3 color = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f),
      float shininess = 32.0f, unsigned int textureID = 0, unsigned int normalMapID = 0)
      : color(color), specular(specular), shininess(shininess), textureID(textureID), normalMapID(normalMapID) {
      }

   // Set material properties in the shader
   void setMaterialProperties(Shader& shader);
   };
