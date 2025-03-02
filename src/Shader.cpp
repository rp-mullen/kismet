
#include "Shader.h"


   unsigned int ID;

   Shader::Shader(const char* shaderPath) {
      std::ifstream shaderFile(shaderPath);
      if (!shaderFile) {
         std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << shaderPath << std::endl;
         return;
         }

      std::stringstream shaderStream;
      shaderStream << shaderFile.rdbuf();
      std::string shaderCode = shaderStream.str();

      // Print the entire shader file content to debug
      std::cout << "=== Shader File Content ===" << std::endl;
      std::cout << shaderCode << std::endl;
      std::cout << "===========================" << std::endl;

      std::string vertexCode, fragmentCode;
      size_t vertexPos = shaderCode.find("#vertex");
      size_t fragmentPos = shaderCode.find("#fragment");

      if (vertexPos != std::string::npos && fragmentPos != std::string::npos) {
         vertexCode = shaderCode.substr(vertexPos + 7, fragmentPos - (vertexPos + 7));
         fragmentCode = shaderCode.substr(fragmentPos + 9);
         }
      else {
         std::cerr << "ERROR::SHADER::INVALID_SHADER_FORMAT" << std::endl;
         return;
         }

      // Print extracted vertex and fragment shaders
      std::cout << "=== Extracted Vertex Shader ===" << std::endl;
      std::cout << vertexCode << std::endl;
      std::cout << "=== Extracted Fragment Shader ===" << std::endl;
      std::cout << fragmentCode << std::endl;

      const char* vShaderCode = vertexCode.c_str();
      const char* fShaderCode = fragmentCode.c_str();

      unsigned int vertex, fragment;
      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &vShaderCode, NULL);
      glCompileShader(vertex);
      checkCompileErrors(vertex, "VERTEX");

      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &fShaderCode, NULL);
      glCompileShader(fragment);
      checkCompileErrors(fragment, "FRAGMENT");

      ID = glCreateProgram();
      glAttachShader(ID, vertex);
      glAttachShader(ID, fragment);
      glLinkProgram(ID);
      checkCompileErrors(ID, "PROGRAM");

      glDeleteShader(vertex);
      glDeleteShader(fragment);

      std::cout << "Shader loaded successfully!" << std::endl;
      }


   void Shader::use() { glUseProgram(ID); }

   void Shader::setInt(const std::string& name, int value) const {
      glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
      }

   void Shader::setFloat(const std::string& name, float value) const {
      glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
      }

   void Shader::setVec3(const std::string& name, glm::vec3 value) const {
      glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
      }

   void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const {
      GLint location = glGetUniformLocation(ID, name.c_str()); // Get the location of the uniform
      if (location == -1) {
         std::cerr << "Warning: Uniform '" << name << "' not found in shader program" << std::endl;
         }
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // Send the matrix to the shader
      }

   void Shader::checkCompileErrors(unsigned int shader, std::string type) {
      int success;
      char infoLog[1024];

      if (type != "PROGRAM") {
         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
         if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
         }
      else {
         glGetProgramiv(shader, GL_LINK_STATUS, &success);
         if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            }
         }
      }

