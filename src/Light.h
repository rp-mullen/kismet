#ifndef LIGHT_H
#define LIGHT_H

#include "Shader.h"

class Light {
public:
  // Light properties
  glm::vec3 position;    // Position of the light (used for point and spot lights)
  glm::vec3 direction;   // Direction of the light (used for directional and spot lights)
  glm::vec3 color;       // Color of the light
  float intensity;       // Intensity of the light

  // Attenuation factors (for point and spot lights)
  float constant;        // Constant attenuation
  float linear;          // Linear attenuation
  float quadratic;       // Quadratic attenuation

  // Spotlight properties (for spotlights)
  float cutOff;          // Cutoff angle for the spotlight
  float outerCutOff;     // Outer cutoff angle for the spotlight

  // Light types enum
  enum class Type {
     Directional,
     Point,
     Spot
     };

  Type lightType;        // Type of light (directional, point, or spotlight)

  bool operator==(const Light& other) const {
     return (position == other.position) && (color == other.color) && (intensity == other.intensity);
     }

  // Constructor for a point light
  Light(glm::vec3 pos, glm::vec3 col, float inten, float con = 1.0f, float lin = 0.09f, float quad = 0.032f)
     : position(pos), color(col), intensity(inten), constant(con), linear(lin), quadratic(quad), lightType(Type::Point) {
     direction = glm::vec3(0.0f);  // Direction is not used for point lights
     cutOff = glm::radians(12.5f);  // Default spotlight cut-off angle
     outerCutOff = glm::radians(15.0f);  // Default outer cut-off angle
     }

  // Constructor for a directional light
  Light(glm::vec3 dir, glm::vec3 col, float inten)
     : direction(glm::normalize(dir)), color(col), intensity(inten), constant(1.0f), linear(0.0f), quadratic(0.0f), lightType(Type::Directional) {
     position = glm::vec3(0.0f);  // Position is not used for directional lights
     cutOff = glm::radians(12.5f);
     outerCutOff = glm::radians(15.0f);
     }

  // Constructor for a spotlight
  Light(glm::vec3 pos, glm::vec3 dir, glm::vec3 col, float inten, float cutOffAngle, float outerCutOffAngle)
     : position(pos), direction(glm::normalize(dir)), color(col), intensity(inten), cutOff(glm::radians(cutOffAngle)), outerCutOff(glm::radians(outerCutOffAngle)), lightType(Type::Spot) {
     constant = 1.0f;
     linear = 0.09f;
     quadratic = 0.032f;
     }

  // Get light information for shaders (used to pass light info to shaders)
  void GetLightData(int index, GLuint shaderID) const {
     std::string lightTypeStr = (lightType == Type::Directional) ? "directional" : (lightType == Type::Point) ? "point" : "spot";

     // Set light properties in the shader
     glUniform3fv(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].position").c_str()), 1, &position[0]);
     glUniform3fv(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].direction").c_str()), 1, &direction[0]);
     glUniform3fv(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].color").c_str()), 1, &color[0]);
     glUniform1f(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].intensity").c_str()), intensity);

     // Point light attenuation factors
     if (lightType == Type::Point) {
        glUniform1f(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].constant").c_str()), constant);
        glUniform1f(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].linear").c_str()), linear);
        glUniform1f(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].quadratic").c_str()), quadratic);
        }

     // Spotlight cutoffs
     if (lightType == Type::Spot) {
        glUniform1f(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].cutOff").c_str()), cutOff);
        glUniform1f(glGetUniformLocation(shaderID, ("lights[" + std::to_string(index) + "].outerCutOff").c_str()), outerCutOff);
        }
     }

  // New method to set light properties in the shader
  void setLightProperties(const Shader& shader, const std::string& lightName) const {
     shader.setVec3(lightName + "position", position);
     shader.setVec3(lightName + "direction", direction);
     shader.setVec3(lightName + "color", color);
     shader.setFloat(lightName + "intensity", intensity);

     if (lightType == Type::Point) {
        shader.setFloat(lightName + "constant", constant);
        shader.setFloat(lightName + "linear", linear);
        shader.setFloat(lightName + "quadratic", quadratic);
        }

     if (lightType == Type::Spot) {
        shader.setFloat(lightName + "cutOff", cutOff);
        shader.setFloat(lightName + "outerCutOff", outerCutOff);
        }
     }
  };
#endif