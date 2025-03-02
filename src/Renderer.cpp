// Renderer.cpp
#include "Renderer.h"
#include "Shader.h"

Renderer::Renderer() {
   shaderManager.loadShader("default", "C:\\Users\\rpm\\source\\repos\\3DEngine\\shaders\\default.glsl");

   currentShader = &shaderManager.getShader("default");
   currentShader->use();

   currentShader->setVec3("lightPos", glm::vec3(1.0f, 1.0f, 1.0f)); // Example light position
   currentShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
   currentShader->setVec3("objectColor", glm::vec3(0.8f, 0.3f, 0.2f));
   }

void Renderer::addModel(const Model& model) {
   models.push_back(model);
   }

void Renderer::removeModel(const Model& model) {
   models.erase(std::remove(models.begin(), models.end(), model), models.end());
   }

void Renderer::render() {
   uploadUniforms(); // Upload global uniforms like lights, camera, etc.

   if (!currentShader) return; // Ensure currentShader is valid
   currentShader->use();

   // Render all models
   for (Model& model : models) {
      glm::mat4 modelMatrix = model.getModelMatrix();
      currentShader->setMat4("model", modelMatrix);
      model.Draw(*currentShader);
      }
   }

void Renderer::uploadUniforms() {
   if (!currentShader) return;

   // Upload global uniforms like camera and light properties
   glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
   glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

   currentShader->use();
   //currentShader->setMat4("view", view);
   //currentShader->setMat4("projection", projection);

   // Set light properties (for example, a point light)
   currentShader->setVec3("light.position", glm::vec3(1.0f, 1.0f, 1.0f));
   currentShader->setVec3("light.color", glm::vec3(1.0f, 1.0f, 1.0f)); // White light
   }
