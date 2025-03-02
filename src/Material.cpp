// Material.cpp
#include "Material.h"
#include "Shader.h"

void Material::setMaterialProperties(Shader& shader) {
   // Set material color
   shader.setVec3("material.color", color);
   shader.setVec3("material.specular", specular);
   shader.setFloat("material.shininess", shininess);

   // Set textures if they exist
   if (textureID) {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textureID);
      shader.setInt("material.diffuse", 0); // Texture unit 0 for diffuse map
      }

   if (normalMapID) {
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, normalMapID);
      shader.setInt("material.normalMap", 1); // Texture unit 1 for normal map
      }
   }
