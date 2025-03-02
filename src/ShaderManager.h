
#pragma once
#include <unordered_map>
#include <string>
#include "Shader.h"

class ShaderManager {
public:
   ShaderManager() = default;

   Shader& getCurrentShader() const { return *currentShader; }

   // Load shader and store it with a unique name
   void loadShader(const std::string& name, const char* shaderPath);

   // Get shader by name
   Shader& getShader(const std::string& name);

private:
   std::unordered_map<std::string, Shader> shaders;
   Shader* currentShader = nullptr;
   };