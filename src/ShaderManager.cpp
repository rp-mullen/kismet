#include "ShaderManager.h"


   void ShaderManager::loadShader(const std::string& name, const char* shaderPath) {
      Shader shader(shaderPath);
      shaders[name] = shader;
      }

   Shader& ShaderManager::getShader(const std::string& name)
      {
      return shaders.at(name); // Use `at` to handle missing keys
      }