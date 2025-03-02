#ifndef SHADER_H
#define SHADER_H
#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
   GLuint ID;
   Shader() = default;
   Shader(const char* shaderPath);
   void use();
   void setBool(const std::string& name, bool value) const;
   void setInt(const std::string& name, int value) const;
   void setVec3(const std::string& name, glm::vec3 value) const;
   void setFloat(const std::string& name, float value) const;
   void setMat4(const std::string& name, const glm::mat4& matrix) const;

   void checkCompileErrors(unsigned int shader, std::string type);
   };

#endif